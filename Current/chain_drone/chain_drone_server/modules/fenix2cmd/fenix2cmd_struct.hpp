#ifndef FENIX2CMD_STRUCT_HPP
#define FENIX2CMD_STRUCT_HPP

// Команды, отправляемые от клиента на сервер

#pragma pack(push,1)
struct Fenix2Cmd
{
    float track_init_posx   = 0; // положение трека по x, pix
    float track_init_posy   = 0; // положение трека по у, pix
    float mouse_pos_x       = 0;
    float mouse_pos_y       = 0;
    int quit_server         = 0; // команда завершения работы сервера
    int track_size_up       = 0; // команда увеличения рамки трека
    int track_size_down     = 0; // команда уменьшения рамки трека
    int init_track          = 0; // команда инициализации трека
    int deinit_track        = 0; // команда деинициализации трека
    int poweroff_srv        = 0; // команда отключения питания на сервереb
    int reinit              = 0;
    int work_mode           = 0; // 0 - на АП посылаем (0,0,0), 1 - сервер посылает АП данные по положению мыши, 2 - сервер посылает АП  данные по положению трекера
    bool mode_track = 0; // подтвердили передачу по результатам поиска нейросетью
    bool mode_mouse = 0;

    bool operator == (const Fenix2Cmd &tmp) const
    {
        return
                (this->quit_server == tmp.quit_server &&
                 this->track_size_up == tmp.track_size_up &&
                 this->track_size_down == tmp.track_size_down &&
                 this->init_track == tmp.init_track &&
                 this->track_init_posx == tmp.track_init_posx &&
                 this->track_init_posy == tmp.track_init_posy &&
                 this->deinit_track == tmp.deinit_track &&
                 this->poweroff_srv == tmp.poweroff_srv &&
                 this->reinit == tmp.reinit &&
                 this->work_mode == tmp.work_mode &&
                 this->mouse_pos_x == tmp.mouse_pos_x &&
                 this->mouse_pos_x == tmp.mouse_pos_x &&
                 this->mode_track == tmp.mode_track &&
                 this->mode_mouse == tmp.mode_mouse);
    }
    bool operator != (const Fenix2Cmd &tmp) const
    {
        return
                (this->quit_server != tmp.quit_server ||
                this->track_size_up != tmp.track_size_up ||
                this->track_size_down != tmp.track_size_down ||
                this->init_track != tmp.init_track ||
                this->track_init_posx != tmp.track_init_posx ||
                this->track_init_posy != tmp.track_init_posy ||
                this->deinit_track != tmp.deinit_track ||
                this->poweroff_srv != tmp.poweroff_srv ||
                this->reinit != tmp.reinit ||
                this->work_mode != tmp.work_mode ||
                this->mouse_pos_x != tmp.mouse_pos_x ||
                this->mouse_pos_x != tmp.mouse_pos_x ||
                this->mode_track != tmp.mode_track ||
                this->mode_mouse != tmp.mode_mouse);
    }
};
#pragma pack(pop)

#endif // FENIX2CMD_STRUCT_HPP
