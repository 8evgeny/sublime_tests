#include <QApplication>
#include <QSettings>

#include "duplo_main_window.h"

int main(int argc, char** argv) {

// Создаем главный объект приложения - app
      QApplication app(argc, argv);

// Создаем объект - главное окно
      DuploMainWindow main_window;

      {
//Объект settings c начальными настройками
        QSettings settings("duplo_sending.ini", QSettings::IniFormat);
        settings.beginGroup("duplo_connection");
        {
          if (!settings.contains("host")) {

//По умолчанию  localhost:8093  в случае реального хоста - адрес прописать в duplo_sending.ini
            settings.setValue("host", "localhost:8093");
          }
          const auto host = settings.value("host").toString();
//Передаем методу SetConnectParam адрес хоста
          main_window.SetConnectParam(host);
        }

        settings.endGroup();
      }

      main_window.Init();

      main_window.show();

      return app.exec();
}
