// 2. Создать класс, инкапсулирующий источник времени для приложения.
//Интерфейс класса:
#include "main.h"

class SystemClock {
 public:
  static int64_t get_time_milliseconds();
};
