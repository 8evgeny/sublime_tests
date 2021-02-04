#include <QApplication>
#include <QSettings>

#include "duplo_main_window.h"

int main(int argc, char** argv) {
  QApplication app(argc, argv);

  DuploMainWindow main_window;

  {
    QSettings settings("duplo_sending.ini", QSettings::IniFormat);
    settings.beginGroup("duplo_connection");
    {
      if (!settings.contains("host")) {
        settings.setValue("host", "localhost:8093");
      }
      const auto host = settings.value("host").toString();

      main_window.SetConnectParam(host);
    }

    settings.endGroup();
  }

  main_window.Init();

  main_window.show();

  return app.exec();
}
