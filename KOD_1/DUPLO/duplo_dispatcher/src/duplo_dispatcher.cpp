#include "duplo_dispatcher.h"
#include <unicode/unistr.h>
#include <cctype>
#include <chrono>
#include <thread>
#include "MessengerServiceSoapBinding.nsmap"
#include "duplo_dispatcher_exception.h"

const std::string kRecievedLogFile = "recv_logfile.log";
const std::string kXmlLogDir = "log_xml/";

namespace sadko {

DuploDispatcher::DuploDispatcher(const char* host)
    : _proxy(std::make_shared<MessengerServiceSoapBindingProxy>(
          host, SOAP_IO_DEFAULT | SOAP_C_UTFSTRING | SOAP_IO_KEEPALIVE)) {}

DuploDispatcher::~DuploDispatcher() { _proxy->destroy(); }

void DuploDispatcher::SendMessage(const ViolationOrder& violation_order) {
  ns1__process request;
  ns1__trCheckIn check_in;
  ns1__message message;
  request.message = &message;
  message.tr_USCOREcheckIn = &check_in;
  ns1__processResponse response;

  check_in.v_USCOREcamera = violation_order.camera();

  auto place = violation_order.cameraPlace();
  check_in.v_USCOREcamera_USCOREplace = &place;

  auto speed = violation_order.speedStr();
  check_in.v_USCOREspeed = &speed;

  auto speed_limit = violation_order.speedLimit();
  check_in.v_USCOREspeed_USCORElimit = &speed_limit;

  check_in.v_USCOREtime_USCOREcheck = violation_order.timestamp();

  auto latitude = violation_order.latitudeStr();
  check_in.v_USCOREgps_USCOREy = &latitude;

  auto longitude = violation_order.longitudeStr();
  check_in.v_USCOREgps_USCOREx = &longitude;

  auto direction = violation_order.directionStr();
  check_in.v_USCOREdirection = &direction;

  auto lane_num = violation_order.laneNumber();
  check_in.v_USCORElane_USCOREnum = &lane_num;

  auto recognition_accuracy = violation_order.recognitionAccuracyStr();
  check_in.v_USCORErecognition_USCOREaccuracy = &recognition_accuracy;

  auto reg_number = violation_order.registrationNumber();
  check_in.v_USCOREregno = &reg_number;

  auto country = violation_order.country();
  check_in.v_USCOREregno_USCOREcountry_USCOREid = &country;

  check_in.v_USCOREpr_USCOREviol.push_back(violation_order.violationCode());

  auto addImage = [](xsd__base64Binary* image,
                     const ViolationOrder::Content& content) {
    if (content.data.empty()) return;
    image->type = const_cast<char*>(content.mime.c_str());
    image->__ptr = const_cast<unsigned char*>(content.data.data());
    image->__size = static_cast<int>(content.data.size());
  };

  check_in.v_USCOREphoto_USCOREts = soap_new_xsd__base64Binary(_proxy.get());
  addImage(check_in.v_USCOREphoto_USCOREts, violation_order.mainPhoto());

  check_in.v_USCOREphoto_USCOREgrz = soap_new_xsd__base64Binary(_proxy.get());
  addImage(check_in.v_USCOREphoto_USCOREgrz, violation_order.platePhoto());

  for (auto& addition_data : violation_order.additionalData()) {
    auto extra = message.photo_USCOREextra.emplace_back(
        soap_new_ns1__photoExtra(_proxy.get()));

    extra->v_USCOREphoto_USCOREextra = soap_new_xsd__base64Binary(_proxy.get());
    addImage(extra->v_USCOREphoto_USCOREextra, addition_data.content);

    extra->v_USCOREtype_USCOREphoto =
        const_cast<std::string*>(&addition_data.type);

    extra->v_USCOREframe_USCOREdatetime =
        const_cast<time_t*>(&addition_data.timestmap);
  }

  int gsoap_code;
  bool resend = false;
  int counter = 0;

  soap_set_recv_logfile(_proxy.get(), kRecievedLogFile.c_str());
  auto file = kXmlLogDir + violation_order.camera() + "_" +
              std::to_string(violation_order.timestamp()) + "_" +
              std::to_string(violation_order.violationCode()) + ".xml";

  soap_set_sent_logfile(_proxy.get(), file.c_str());

  while (!resend) {
    gsoap_code = _proxy->process(&request, response);

    switch (gsoap_code) {
      case SOAP_OK:
        resend = true;
        break;

      case SOAP_FAULT: {
        auto duplo_code =
            _proxy->fault->SOAP_ENV__Detail->ns1__DuploFault->faultCode;
        auto duplo_message =
            _proxy->fault->SOAP_ENV__Detail->ns1__DuploFault->faultMessage;

        auto IsSqlError = [](const std::string& code) -> bool {
          return code == "SQL_08003" || code == "SQL_08006";
        };

        if (!IsSqlError(*duplo_code)) {
          throw SOAPDuploFault(static_cast<u_char>(gsoap_code), *duplo_code,
                               *duplo_message);
        }

        ++counter;

        if (counter > _max_resend_number_on_error) {
          // todo: sql fault exception
          throw SOAPDuploFaultSql(static_cast<u_char>(gsoap_code));
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(_delay));
      } break;

      case SOAP_UDP_ERROR:
      case SOAP_TCP_ERROR:

        throw SOAPConnectionException(static_cast<u_char>(gsoap_code));

      default:

        throw SOAPDuploException(static_cast<u_char>(gsoap_code));
    }
  }
}

void DuploDispatcher::SetMessengerService(ProxyPtrS proxy) { _proxy = proxy; }
}  // namespace sadko
