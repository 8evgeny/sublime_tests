#include "duplo_main_window.h"

// Qt
#include <QDir>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QTableView>

// library
#include "images_model.h"

// third party
#include <easy/profiler.h>

//Конструктор класса
    DuploMainWindow::DuploMainWindow(QWidget* parent)
        : QMainWindow(parent), _dispatcher("localhost:8093") {}

//Реализация функции SetConnectParam(const QString& host)
    void DuploMainWindow::SetConnectParam(const QString& host) {
    //Создаем символьный массив
      static char connect[1024] = {0};

    //Преобразовываем адрес хоста в формат gSOAP
      strncpy(connect, host.toUtf8().data(), static_cast<size_t>(host.size()));

    //Создаем умный указатель proxy на структуру, которая преобразует данные в XML
      auto proxy = std::make_shared<MessengerServiceSoapBindingProxy>(
          connect, SOAP_IO_DEFAULT | SOAP_C_UTFSTRING | SOAP_IO_KEEPALIVE);

    //_dispatcher - объект класса DuploDispatcher реализует метод класса - установку адреса прокси
      _dispatcher.SetMessengerService(proxy);

    //Заголовок главного окна
      setWindowTitle("Duplo sender");

    //Если нет директории "log_xml" то создаем ее
      if (!QDir("log_xml").exists()) {
        QDir().mkdir("log_xml");
      }
    }

//Реализация функции Init()
    void DuploMainWindow::Init() {
    //Профилирование
      EASY_MAIN_THREAD;
      EASY_PROFILER_ENABLE
      profiler::startListen();

    //создаем новый Qt-объект - widget
      auto widget = new QWidget;
    //назначаем его главным виджетом
      setCentralWidget(widget);

    //создаем новый Qt-объект - main_layout с горизонтальным размещением элементов
      auto main_layout = new QHBoxLayout;
    //помещаем его в главный виджет
      widget->setLayout(main_layout);

      {
/* Создаем новый объект _widgets класса ViolationOrderWidget структуры Widget
 * при этом также создаются следующие объеты
 * _violation_order - объект класса ViolationOrder
 * _images - объект класса Images
 * _path_to_files - объект класса QString
 * _dispatcher - объект класса Dispatcher*     */
         _widgets.violation_order = new ViolationOrderWidget;

// Устанавливается отправщик сообщения
        _widgets.violation_order->SetDispatcher(&_dispatcher);

//Виджет запускается
        _widgets.violation_order->Init();

//Виджет добавляется в главное окно
        main_layout->addWidget(_widgets.violation_order);
      }

      {
//Таблица добавляется в главное окно
        auto table_view = new QTableView;
        table_view->horizontalHeader()->setStretchLastSection(true);
        main_layout->addWidget(table_view);

//Создаем новый объект класса ImagesModel
        auto model = new ImagesModel(table_view);
        table_view->setModel(model);
        table_view->horizontalHeader()->setSectionResizeMode(
            QHeaderView::ResizeToContents);
// ??
        connect(_widgets.violation_order, &ViolationOrderWidget::ResetImages, model,
                &ImagesModel::ResetImages);
        connect(_widgets.violation_order, &ViolationOrderWidget::SendImages, model,
                &ImagesModel::RecievedImages);

    //    connect(model, &ImagesModel::modelReset, [table_view]() {

    //    });
  }
}
