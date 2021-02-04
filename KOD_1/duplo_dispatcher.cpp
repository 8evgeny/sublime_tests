#include "duplo_dispatcher.h"
#include <unicode/unistr.h>
#include <cctype>
#include <chrono>
#include <thread>
#include "MessengerServiceSoapBinding.nsmap"
#include "duplo_dispatcher_exception.h"

//Имена лог-файла и лог-директории
    const std::string kRecievedLogFile = "recv_logfile.log";
    const std::string kXmlLogDir = "log_xml/";

    namespace sadko {

/*Конструктор класса DuploDispatcher, инициализируется через умный указатель
_proxy на структуру, которая преобразует данные в XML  */
    DuploDispatcher::DuploDispatcher(const char* host)
        : _proxy(std::make_shared<MessengerServiceSoapBindingProxy>(
              host, SOAP_IO_DEFAULT | SOAP_C_UTFSTRING | SOAP_IO_KEEPALIVE)) {}

//При вызове деструктора закрыть соединение
    DuploDispatcher::~DuploDispatcher() { _proxy->destroy(); }

/*Реализация метода SendMessage класса DuploDispatcher
на вход принимает ссылку на объект violation_order - заполненную
структуру с данными по нарушению */
    void DuploDispatcher::SendMessage(const ViolationOrder& violation_order) {

/*создаем объекты класов SOAP -
 * request, check_in, message, response
 * При передаче данных вызывается метод process,
 * которому передает сообщение message с (комплексными) полями проездов trCheckIn
 * (обязательная часть сообщения) и (необязательным) массивом дополнительных
 * фотоматериалов с (комплексными) полями «photoExtra».  */
      ns1__process request;
      ns1__trCheckIn check_in; //check_in  мы будем заполнять из объекта  violation_order
      ns1__message message;

      request.message = &message;
      message.tr_USCOREcheckIn = &check_in;
      ns1__processResponse response;

//номер камеры
      check_in.v_USCOREcamera = violation_order.camera();

//Местоположение камеры
      auto place = violation_order.cameraPlace();
      check_in.v_USCOREcamera_USCOREplace = &place;

//скорость
      auto speed = violation_order.speedStr();
      check_in.v_USCOREspeed = &speed;

//предел скорости
      auto speed_limit = violation_order.speedLimit();
      check_in.v_USCOREspeed_USCORElimit = &speed_limit;

//время
      check_in.v_USCOREtime_USCOREcheck = violation_order.timestamp();

//долгота и широта
      auto latitude = violation_order.latitudeStr();
      check_in.v_USCOREgps_USCOREy = &latitude;

      auto longitude = violation_order.longitudeStr();
      check_in.v_USCOREgps_USCOREx = &longitude;

//направление движения
      auto direction = violation_order.directionStr();
      check_in.v_USCOREdirection = &direction;

//номер полосы
      auto lane_num = violation_order.laneNumber();
      check_in.v_USCORElane_USCOREnum = &lane_num;

//точность распознавания (от 0 до 100)
      auto recognition_accuracy = violation_order.recognitionAccuracyStr();
      check_in.v_USCORErecognition_USCOREaccuracy = &recognition_accuracy;

//Регистрационный номер
      auto reg_number = violation_order.registrationNumber();
      check_in.v_USCOREregno = &reg_number;

//Страна
      auto country = violation_order.country();
      check_in.v_USCOREregno_USCOREcountry_USCOREid = &country;

//Код нарушения
      check_in.v_USCOREpr_USCOREviol.push_back(violation_order.violationCode());

//Структура GSOAP
      auto addImage = [](xsd__base64Binary* image,
                         const ViolationOrder::Content& content) {
        if (content.data.empty()) return;
        image->type = const_cast<char*>(content.mime.c_str());
        image->__ptr = const_cast<unsigned char*>(content.data.data());
        image->__size = static_cast<int>(content.data.size());
      };
//Главное фото
      check_in.v_USCOREphoto_USCOREts = soap_new_xsd__base64Binary(_proxy.get());
      addImage(check_in.v_USCOREphoto_USCOREts, violation_order.mainPhoto());

//Фото ГРЗ
      check_in.v_USCOREphoto_USCOREgrz = soap_new_xsd__base64Binary(_proxy.get());
      addImage(check_in.v_USCOREphoto_USCOREgrz, violation_order.platePhoto());

//Отправка дополнительного контента
      for (auto& addition_data : violation_order.additionalData())
            {
//Формируем объект extra
            auto extra = message.photo_USCOREextra.emplace_back(
                soap_new_ns1__photoExtra(_proxy.get()));
//Доп. контент
            extra->v_USCOREphoto_USCOREextra = soap_new_xsd__base64Binary(_proxy.get());
            addImage(extra->v_USCOREphoto_USCOREextra, addition_data.content);

// тип дополнительной фотографии
            extra->v_USCOREtype_USCOREphoto =
                const_cast<std::string*>(&addition_data.type);
//Дата время
            extra->v_USCOREframe_USCOREdatetime =
                const_cast<time_t*>(&addition_data.timestmap);
            }

      int gsoap_code;
      bool resend = false;
      int counter = 0;

//Принимаем лог файл
      soap_set_recv_logfile(_proxy.get(), kRecievedLogFile.c_str());

// Формируем лог-файл который отправляем
      auto file = kXmlLogDir + violation_order.camera() + "_" +
                  std::to_string(violation_order.timestamp()) + "_" +
                  std::to_string(violation_order.violationCode()) + ".xml";

//Отправляем лог файл
      soap_set_sent_logfile(_proxy.get(), file.c_str());

//Процесс отправки
      while (!resend) {
        gsoap_code = _proxy->process(&request, response);

        switch (gsoap_code) {
          case SOAP_OK:
            resend = true;
            break;
//Если возникли ошибки получаем код - duplo_code
          case SOAP_FAULT: {
            auto duplo_code =
                _proxy->fault->SOAP_ENV__Detail->ns1__DuploFault->faultCode;

//Получаем сообщение - duplo_message
            auto duplo_message =
                _proxy->fault->SOAP_ENV__Detail->ns1__DuploFault->faultMessage;

// Устанавливаем коды ошибок SQL по которым будем повторно отправлять
            auto IsSqlError = [](const std::string& code) -> bool {
              return code == "SQL_08003" || code == "SQL_08006";
            };

//Если ошибка не SQL - вызываем исключение
            if (!IsSqlError(*duplo_code)) {
              throw SOAPDuploFault(static_cast<u_char>(gsoap_code), *duplo_code,
                                   *duplo_message);
            }

            ++counter;

//Если превышено число попыток - вызываем исключение ош записи SQL
            if (counter > _max_resend_number_on_error) {
              // todo: sql fault exception
              throw SOAPDuploFaultSql(static_cast<u_char>(gsoap_code));
            }
//ждем милисекунд _delay
            std::this_thread::sleep_for(std::chrono::milliseconds(_delay));
          } break;

          case SOAP_UDP_ERROR:
          case SOAP_TCP_ERROR:
//Если ошибка соединения - вызываем исключение
            throw SOAPConnectionException(static_cast<u_char>(gsoap_code));

          default:
//Вызываем исключение - другой тип ошибки
            throw SOAPDuploException(static_cast<u_char>(gsoap_code));
        }
      }
    }


//Реализация метода SetMessengerService класса DuploDispatcher
    void DuploDispatcher::SetMessengerService(ProxyPtrS proxy) { _proxy = proxy; }
}  // namespace sadko
