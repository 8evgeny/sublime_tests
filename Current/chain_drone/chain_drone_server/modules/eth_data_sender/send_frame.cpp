#include "send_frame.hpp"

using namespace std;
using namespace cv;

int main()
{
    /// Создали и настроили класс отправитель метаданных (условный сервер)
    bool ok = 0;
    string config_path = "../eth_ini_send.ini";
    unique_ptr<EthSender> eth_sender_ptr = nullptr;
    eth_sender_ptr = make_unique<EthSender>(config_path, ok);


    if (!ok) {cout << "ERROR: can't init EthSender!\nEND main!" << endl; return 0; }

    /// device
    VideoCapture cap;
    cap.open("/home/hasee/data_sets/jukovsky/101MEDIA/DJI_0122.LRF");
    Mat img2send;
    cv::Mat img_black = cv::Mat(Size(1280,720), CV_8UC1, Scalar(0));
    namedWindow("send", WINDOW_NORMAL);
    imshow("send", img_black);
    char key = waitKey(1);
    float counter = 0 ;
    Fenix2Meta meta_fenix2send_folder;

    while(true)
    {
        key = waitKey(1);
        if (key == '`') {cout << "end work!" << endl; break;}

        cap.read(img2send);
        cvtColor(img2send, img2send, COLOR_BGR2GRAY);
        bool ok_send = eth_sender_ptr->frame_mjpg_eth_controller->send_frame(img2send);
        if (ok_send)
        {
            imshow("send", img2send);
            meta_fenix2send_folder.track_is_init = ok_send;
            meta_fenix2send_folder.diff_trackx = counter;
            meta_fenix2send_folder.diff_tracky = counter;
            meta_fenix2send_folder.trackx = counter;
            meta_fenix2send_folder.tracky = counter;
            meta_fenix2send_folder.tp_send = std::chrono::duration_cast<std::chrono::milliseconds>
                    (std::chrono::system_clock::now().time_since_epoch()).count();;


            eth_sender_ptr->fenix2meta_sender_ptr->set(meta_fenix2send_folder);
            counter++;
        }
    } // END  while(true)
    cout << "END main" << endl;
    eth_sender_ptr->frame_mjpg_eth_controller->quit();
    eth_sender_ptr->fenix2meta_sender_ptr->quit();
    return 1;
} // END int main()
