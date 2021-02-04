#include "duplo_sender/duplo_main_window.h"

// Qt
#include <QDir>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QTableView>

// library
#include "images_model.h"

// third party
#include <easy/profiler.h>

DuploMainWindow::DuploMainWindow(QWidget* parent)
    : QMainWindow(parent), _dispatcher("localhost:8093") {}

void DuploMainWindow::SetConnectParam(const QString& host) {
  static char connect[1024] = {0};

  strncpy(connect, host.toUtf8().data(), static_cast<size_t>(host.size()));

  auto proxy = std::make_shared<MessengerServiceSoapBindingProxy>(
      connect, SOAP_IO_DEFAULT | SOAP_C_UTFSTRING | SOAP_IO_KEEPALIVE);

  _dispatcher.SetMessengerService(proxy);

  setWindowTitle("Duplo sender");

  if (!QDir("log_xml").exists()) {
    QDir().mkdir("log_xml");
  }
}

void DuploMainWindow::Init() {
  EASY_MAIN_THREAD;
  EASY_PROFILER_ENABLE
  profiler::startListen();

  auto widget = new QWidget;
  setCentralWidget(widget);

  auto main_layout = new QHBoxLayout;
  widget->setLayout(main_layout);

  {
    _widgets.violation_order = new ViolationOrderWidget;
    _widgets.violation_order->SetDispatcher(&_dispatcher);
    _widgets.violation_order->Init();

    main_layout->addWidget(_widgets.violation_order);
  }

  {
    auto table_view = new QTableView;
    table_view->horizontalHeader()->setStretchLastSection(true);
    main_layout->addWidget(table_view);

    auto model = new ImagesModel(table_view);
    table_view->setModel(model);
    table_view->horizontalHeader()->setSectionResizeMode(
        QHeaderView::ResizeToContents);

    connect(_widgets.violation_order, &ViolationOrderWidget::ResetImages, model,
            &ImagesModel::ResetImages);
    connect(_widgets.violation_order, &ViolationOrderWidget::SendImages, model,
            &ImagesModel::RecievedImages);

    //    connect(model, &ImagesModel::modelReset, [table_view]() {

    //    });
  }
}
