#ifndef META_STRUCT_HPP
#define META_STRUCT_HPP
#include <chrono>
// телеметрия, формируемая на стороне сервера (например, шара)

#pragma pack(push,1)

struct Fenix2Meta
{
    uint32_t num_frame = 0; // device->getId()
    unsigned long long int time_delay_mcs = 0; // задержка между формированием кадра (set(frame) на сервере) и получением (frame(frame) на клиенте) кадра в микросекундах
    bool track_is_init = 0; // состояние инициализации трека
    bool track_confirm = 0; // оператор одобрил установленный трек как корректный
    uint8_t gpu_type = 0;    // тип библиотеки
    uint8_t device  = 0;    // тип девайса
    float trackx = 0;       // положение трека по x
    float tracky = 0;       // положение трека по у
    float new_trackw = 0;   // ширина трека при инициализации
    float new_trackh = 0;   // высота --
    float trackw = 0;       // ширина текщего установленого трека
    float trackh = 0;       // высота --
    float diff_trackx = -1; // разница между положением трека и центром экрана по х
    float diff_tracky = -1; // -- у
    float x_m_s = 0;        // смещение трека по x относительно центра (величину можно установить как dbg::)
    float y_m_s = 0;        // --                у
    float x_m_ss = 0;       //
    float y_m_ss = 0;       //
    float roll_deg = 0;     // телеметрия от Авакса
    float pitch_deg = 0;    //
    float yaw_deg = 0;      //
    float alt_m = 100;      //

    unsigned long long int tp_send = 0; // временная точка отправки фрейма, устанавливемая на сервере dbg::
    unsigned long long int tp_keep = 0; //
    int work_in_round = 0 ;             // признак сканирования в круге при работе с tkdnn
};
#pragma pack(pop)

#endif // META_STRUCT_HPP
