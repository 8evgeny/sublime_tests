#include <iostream>
#include <string>
#include <thread>
#include <condition_variable>
#include <unistd.h>
#include <fstream>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <atomic>
#include <opencv2/core/utility.hpp>
#include "opencv2/imgproc.hpp"
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

string path1 = "run_gui_8UC1_10";  // Путь к библиотеке с нейросетью
string path2 = "run_gui_8UC1_8";  // Путь к библиотеке с трекером

int childPID = 0;
bool exec = true;
Scalar red =  cv::Scalar(0, 0, 255);
Scalar green = cv::Scalar(0, 255, 0);

bool FileIsExist(const string& filePath);
bool IsProcessAlive(int ProcessId);
void stopChildProcess();
void systemSignalsHandler(int sig);

bool FileIsExist(const string& filePath)
{
    // Проверка на существование файла
    bool isExist = false;
    ifstream fin(filePath.c_str());
    if(fin.is_open()){isExist = true;}
    fin.close();
    return isExist;
} // -- END FileIsExist

bool IsProcessAlive(int ProcessId)
{
    // Wait for child process, this should clean up defunct processes
    waitpid(ProcessId, nullptr, WNOHANG);
    // kill failed let's see why..
    if (kill(ProcessId, 0) == -1)
    {
        // First of all kill may fail with EPERM if we run as a different user and we have no access, so let's make sure the errno is ESRCH (Process not found!)
        if (errno != ESRCH) {return true;}
        return false;
    }  // END if (kill(ProcessId, 0) == -1)
    // If kill didn't fail the process is still running
    if(ProcessId == 0) {return false;}
    return true;
} // -- END IsProcessAlive

void stopChildProcess()
{
    // Остановка Ctrl+C дочернего процесса
    if(childPID != 0)
    {
        std::cout << "Close process " <<  childPID << std::endl;
        kill(childPID, SIGTERM);
        int status = 0;
        waitpid(childPID, &status, WNOHANG);
        childPID = 0;
        //exec= true;
    }  // END if(childPID != 0)
}  // END void stopChildProcess()

void systemSignalsHandler(int sig)
{
    // install signal
    signal(sig, SIG_DFL);
    stopChildProcess();
    exec = false;
}  // END void systemSignalsHandler(int sig)

int main()
{
    // Install a signal handler
    signal(SIGINT,  systemSignalsHandler);
    signal(SIGHUP,  systemSignalsHandler);
    signal(SIGABRT, systemSignalsHandler);
    signal(SIGTERM, systemSignalsHandler);
    signal(SIGKILL, systemSignalsHandler);
    signal(SIGQUIT, systemSignalsHandler);
    signal(SIGSTOP, systemSignalsHandler);
    namedWindow("img");
    Mat img(Size(64, 64), CV_8UC3, Scalar(200, 200, 200));
    char key = 0;
    putText(img, "N1", Point(10, 25), FONT_HERSHEY_COMPLEX, 1, green, 2);
    putText(img, "T2", Point(10, 55), FONT_HERSHEY_COMPLEX, 1, red, 2);

    // вызов библиотеки с нейросетью по умолчанию
    stopChildProcess();
    switch(childPID = fork())
    {
    case -1:
        cout << "Error" << endl;
        break;
    case 0:
        execl(path1.c_str(), NULL);
        break;
    default:
      {
          cout << "Message from base process; Child Process id = " <<  childPID << endl;
          break;
      } // END default
    } // END switch(childPID = fork())

    // Проверка на существование библиотек
    if(!FileIsExist(path1))
    {
        cout << "Error! File " << path1 << " does not exists!" << endl;
        return -1;
    } // END if(FileIsExist(path1))

    if(!FileIsExist(path2))
    {
        cout << "Error! File " << path2 << " does not exists!" << endl;
        return -1;
    } // END if(FileIsExist(path2))

    // Основной цикл
    while(exec)
    {
        imshow("img", img);
        key = waitKey(100);

        // Выход по ESC
        //if(key == 27 && childPID == 0) {break;}

        // Дублирование выхода из дочернего потока
        if(key == '`' || !IsProcessAlive(childPID))
        {
            putText(img, "N1", Point(10, 25), FONT_HERSHEY_COMPLEX, 1, red, 2);
            putText(img, "T2", Point(10, 55), FONT_HERSHEY_COMPLEX, 1, red, 2);
            stopChildProcess();
        }  // END if(key == '`' || !IsProcessAlive(childPID))

        // Выбор библиотеки с нейросетью
        if(key == '1' && !IsProcessAlive(childPID))
        {
            putText(img, "N1", Point(10, 25), FONT_HERSHEY_COMPLEX, 1, green, 2);
            stopChildProcess();
            switch(childPID = fork())
            {
            case -1:
                cout << "Error" << endl;
                break;
            case 0:
                execl(path1.c_str(), NULL);
                break;
            default:
              {
                  cout << "Message from base process; Child Process id = " <<  childPID << endl;
                  break;
              } // END default
            } // END switch(childPID = fork())
        }  // END if(key == '1')

        // Выбор библиотеки с трекером
        if(key == '2' && !IsProcessAlive(childPID))
        {
            putText(img, "T2", Point(10, 55), FONT_HERSHEY_COMPLEX, 1, green, 2);
            stopChildProcess();
            switch(childPID = fork())
            {
            case -1:
                cout << "Error" << endl;
                break;
            case 0:
                execl(path2.c_str(), NULL);
                break;
            default:
              {
                  cout << "Message from base process; Child Process id = " <<  childPID << endl;
                  break;
              } // END default
            } // END switch(childPID = fork())
        }  // END if(key == '2')

    }  // END while(exec)

    destroyAllWindows();
    cout << "END Main vertelka!" << endl;
    return 0;
}  // END main
