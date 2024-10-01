#ifndef ETH_CMD_COMMON_TYPES_HPP
#define ETH_CMD_COMMON_TYPES_HPP

#include <memory>

// namespace eth_cmd_processing
// {

enum EthCommands
{
    ETH_CMD_UNCOMPRESS_FRAME_DEFAULT, // несжатое изображение
    ETH_CMD_COPTER_ALARM, // информация об обнаруженном и сопровождаемом объекте на видео потоке
    ETH_CMD_TELEMETRY_ATAS, // информация о состоянии работы АТАС
    ETH_CMD_POWEROFF_REQUEST, // запрос на выключение соединенного 
    ETH_CMD_CONFIRM_CMD_RECEIVE, // подтверждение поступления какой-либо (определенной) команды
    ETH_CMD_AP_TELEMETRY, // paritel telemetry from AutoPilot
    ETH_CMD_CHAIN_DRONE_AP_TELEMETRY,
    ETH_CMD_TRACKER_METADATA, // PARITEL
    ETH_CMD_TRACKER_METADATA_POS, // PARITEL
    ETH_CMD_ORIENTATION_TELEMETRY, // телеметрия pitch, roll, yaw
    ETH_CMD_AP_POS_CNT, // команда управления положением БПЛА для автопилота
    ETH_CMD_FENIX2_METADATA, // передача телеметрии fenix2
    ETH_CMD_FENIX2_CMD_DATA, // передача команд от клиента к серверу fenix2
    ETH_CMD_NO_COMMAND, // значение назначается объекту базового класса по умолчанию (предпоследняя позиция)
    ETH_CMD_LAST_ELEMENT_NO_SHIFT //для определения общего количества команд
}; // END -- EthCommands

// } // -- ns eth_cmd_processing

#endif //ETH_CMD_COMMON_TYPES_HPP
