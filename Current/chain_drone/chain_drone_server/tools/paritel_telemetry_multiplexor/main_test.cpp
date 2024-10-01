#include <iostream>
#include <thread>
#include <string>

#include "esrt_api.hpp"
#include "paritel_telemetry_ap.hpp"
#include "paritel_telemetry_general.hpp"
#include "paritel_telemetry_multiplexor.hpp"

/*
    Тестовая программа для преобразования ESRT или ParitelTelemetryAP в
    универсальный формат телеметрии. Полагается, что вне в зависимости от
    источника телеметрии вызывается или conv_ESRT_to_TeleGen или conv_TeleAP_to_TeleGen.
    Но на выходе универсальная по формату телеметрия для алгоритма трекинга и сохранения 
    (под дальнейшее использование в демонстрационной программе)

    Представлен элементарный минимально воспроизводимый пример взаимодействия по шагам 1,2,3,4.
*/
int main(int argc, char* argv[])
{
    std::string path2esrt = "../test_data/1000001.ESRT";
    ESRTdata esrt_tmp;
    ParitelTelemetryGen tele_gen;
    if(!parseESRT(path2esrt, esrt_tmp))                         // 1. чтение ESRT из файла
    {
        std::cout << "ERROR parse ESRT" << std::endl;
        return 1;
    }
        
    telemetry_mux::conv_ESRT_to_TeleGen(esrt_tmp, tele_gen);    // 2. конвертация ESRT в TeleGen

    float roll = tele_gen.roll_rad;                             // 3. Имитация работы с tele_gen
    float pitch = tele_gen.pitch_rad;
    float yaw = tele_gen.yaw_rad;
    float abcd = 123 * std::cos(roll) * std::sin(yaw * pitch);  // Внимание!! Формула ТОЛЬКО ДЛЯ ПРИМЕРА!

    if(!tele_gen.save2txt("../test_data/1000001.PTD"))          // 4. Сохранение tele_gen в текстовый файл
    {
        std::cout << "ERROR save TeleGen" << std::endl;
        return 1;
    }

    // ParitelTelemetryGen tele_gen1;
    // if(!tele_gen1.readFromTxt("../test_data/1000001.PTD"))
    // {
    //     std::cout << "ERROR load TeleGen" << std::endl;
    // }

    std::cout << "END main" << std::endl;
    return 0;
}
