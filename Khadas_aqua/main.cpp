#include <iostream>
#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <thread>
#include <iomanip>
#include <chrono>
#include <QtCore>
#include <QDebug>
#include <mutex>
#include <fstream>

using namespace std;

const int gpio_pin_UF       = 6;    //PIN22     1_RELE
const int gpio_pin_PUMP_AIR = 7;    //PIN23     2_RELE
const int gpio_pin_FOOD     = 10;   //PIN29     3_RELE
const int gpio_pin_HEAT     = 11;   //PIN30     5_RELE
const int gpio_pin_LAMP     = 12;   //PIN31     6_RELE

const int gpio_pin_COLD     = 13;   //PIN32
const int gpio_pin_REZERV   = 15;   //PIN35



float min_temp, max_temp;
bool heater = false;
float temperature;
QTime time_light_on, time_light_off, time_UF_on, time_UF_off;
vector<QTime> food(0);
QString food_time;
int long_food = 0;
bool light = true;
bool UF = false;
mutex Mut;
ofstream logFile;          // поток для записи
ofstream fileTemperature;
ofstream fileLight_on;
ofstream fileLight_off;
ofstream fileHeat_on;
ofstream fileHeat_off;
ofstream fileStateLight;
ofstream fileStateUF;
ofstream fileStateHeat;
ofstream fileFood;
ofstream fileStateFeed;

constexpr long numLinesInLog = 250;

								//PIN37   onewire  измерение температуры
								//PIN40   GND
								//PIN1    +5
								//PIN2    +5


void printTime(ofstream & file)
{
    const auto now = std::chrono::system_clock::now();
    const auto t_c = std::chrono::system_clock::to_time_t(now);
    file << std::put_time(std::localtime(&t_c), "%T  %d.%b.%y \n");
}
void printOnylTime(ofstream & file)
{
    const auto now = std::chrono::system_clock::now();
    const auto t_c = std::chrono::system_clock::to_time_t(now);
    file << std::put_time(std::localtime(&t_c), "%T\n");
}


void
receiveTemp(float & temperature)
{
    while(1)
    {
        Mut.lock();
        std::string tmp;
        const char *cmd = "/home/khadas/aqua/tempread.sh";
        char buf[BUFSIZ];
        FILE *ptr;
        if ((ptr = popen(cmd, "r")) != NULL)
        {
            while(fgets(buf, BUFSIZ, ptr) != NULL);
            std::string tmp2{buf};
            tmp = tmp2;
            (void) pclose(ptr);
        }
        temperature = std::stof(tmp);
        Mut.unlock();
        this_thread::sleep_for(chrono::milliseconds(60000));
    }
}

void
receiveSettings(float & min_temp, float & max_temp, bool & heater,
                 QTime & time_light_on, QTime & time_light_off, bool & light,
                QTime & time_UF_on, QTime & time_UF_off, bool & UF)
{
    QStringList foodTimes;
    while(1)
    {
        Mut.lock();
        QSettings settings("/home/khadas/aqua/config", QSettings::IniFormat);
        settings.beginGroup("Temperature");
        min_temp = settings.value( "min_temp").toFloat();
        max_temp = settings.value( "max_temp").toFloat();
        heater = settings.value( "heater").toBool();
        settings.endGroup();

        settings.beginGroup("Light");
        time_light_on = QTime::fromString(settings.value( "time_light_on").toString());
        time_light_off = QTime::fromString(settings.value( "time_light_off").toString());
        light = settings.value( "light").toBool();
        settings.endGroup();

        settings.beginGroup("UF");
        time_UF_on = QTime::fromString(settings.value( "time_UF_on").toString());
        time_UF_off = QTime::fromString(settings.value( "time_UF_off").toString());
        UF = settings.value( "UF").toBool();
        settings.endGroup();

        settings.beginGroup("Food");
        foodTimes = settings.value( "time_Food").toStringList();
        food.clear();
        food_time.clear();
        for (int i = 0; i<foodTimes.size(); ++i)
        {
            food.push_back(QTime::fromString(foodTimes.at(i)));
            food_time.push_back(foodTimes.at(i));
            food_time.push_back("    ");
        }
        long_food = settings.value( "long_Food").toInt();
        settings.endGroup();

        Mut.unlock();
        this_thread::sleep_for(chrono::milliseconds(1000));
    }
}

void
handlerLight(bool & light, QTime & time_light_on, QTime & time_light_off)
{
    this_thread::sleep_for(chrono::milliseconds(5000));
    string stateLight = "none";
    while(1)
    {
        Mut.lock();
        logFile.open("/home/khadas/aqua/logFile", std::ios::app);
        if (!light)
        {
            digitalWrite(gpio_pin_LAMP, HIGH);
            if (stateLight != "OFF")
            {
                logFile << "######## light set OFF #######" <<"\t\t";
                printTime(logFile);
                stateLight = "OFF";
                fileStateLight.open("/home/khadas/aqua/for_web/state_light", std::ios::out);
                fileStateLight <<"OFF     ";
                printTime(fileStateLight);
                fileStateLight.close();
            }
        }
        if (light)
        {
            auto timeNow = QTime::currentTime();
            if ( (timeNow > time_light_on) && (timeNow < time_light_off) && (temperature < 27.5)
                    && (stateLight != "ON") )
            {
                digitalWrite(gpio_pin_LAMP, LOW);
                logFile << "######## light set ON ########"  <<"\t\t";
                printTime(logFile);
                stateLight = "ON";
                fileStateLight.open("/home/khadas/aqua/for_web/state_light", std::ios::out);
                fileStateLight <<"ON     ";
                printTime(fileStateLight);
                fileStateLight.close();
            }
            if ( (!((timeNow > time_light_on) &&  (timeNow < time_light_off)) || (temperature > 27.7))
                 && (stateLight != "OFF") )
            {
                digitalWrite(gpio_pin_LAMP, HIGH);
                logFile << "######## light set OFF ########"  <<"\t\t";
                printTime(logFile);
                stateLight = "OFF";
                fileStateLight.open("/home/khadas/aqua/for_web/state_light", std::ios::out);
                fileStateLight <<"OFF     ";
                printTime(fileStateLight);
                fileStateLight.close();
            }
        }
        logFile.close();
        Mut.unlock();
        this_thread::sleep_for(chrono::milliseconds(1000));
    }
}

void
handlerUF(bool & UF, QTime & time_UF_on, QTime & time_UF_off)
{
    this_thread::sleep_for(chrono::milliseconds(5000));
    string stateUF = "none";
    while(1)
    {
        Mut.lock();
        logFile.open("/home/khadas/aqua/logFile", std::ios::app);
        if (!UF)
        {
            digitalWrite(gpio_pin_UF, HIGH);
            if (stateUF != "OFF")
            {
                logFile << "######## UF set OFF #######" <<"\t\t";
                printTime(logFile);
                stateUF = "OFF";
                fileStateUF.open("/home/khadas/aqua/for_web/state_uf", std::ios::out);
                fileStateUF <<"OFF     ";
                printTime(fileStateUF);
                fileStateUF.close();
            }
        }
        if (UF)
        {
            auto timeNow = QTime::currentTime();
            if ((timeNow > time_UF_on) && (timeNow < time_UF_off) && (stateUF != "ON"))
            {
                digitalWrite(gpio_pin_UF, LOW);
                logFile << "######## UF set ON ########"  <<"\t\t";
                printTime(logFile);
                stateUF = "ON";
                fileStateUF.open("/home/khadas/aqua/for_web/state_uf", std::ios::out);
                fileStateUF <<"ON     ";
                printTime(fileStateUF);
                fileStateUF.close();
            }
            if (!((timeNow > time_UF_on) && (timeNow < time_UF_off)) && (stateUF != "OFF"))
            {
                digitalWrite(gpio_pin_UF, HIGH);
                logFile << "######## UF set OFF ########"  <<"\t\t";
                printTime(logFile);
                stateUF = "OFF";
                fileStateUF.open("/home/khadas/aqua/for_web/state_uf", std::ios::out);
                fileStateUF <<"OFF     ";
                printTime(fileStateUF);
                fileStateUF.close();
            }
        }
        logFile.close();
        Mut.unlock();
        this_thread::sleep_for(chrono::milliseconds(1000));
    }
}

void
handlerHeater(bool & heater, float & min_temp, float & max_temp)
{
    this_thread::sleep_for(chrono::milliseconds(5000));
    string stateHeater = "none";
    while(1)
    {
        Mut.lock();
        logFile.open("/home/khadas/aqua/logFile", std::ios::app); // окрываем файл для дозаписи
        if (!heater && stateHeater != "OFF")
        {
            digitalWrite(gpio_pin_HEAT, HIGH);
            logFile << "######## heater set OFF #######" <<"\t\t";
            printTime(logFile);
            stateHeater = "OFF";
            fileStateHeat.open("/home/khadas/aqua/for_web/state_heat", std::ios::out);
            fileStateHeat <<"OFF     ";
            printTime(fileStateHeat);
            fileStateHeat.close();
        }
        if (heater)
        {
            if (temperature > max_temp && stateHeater != "OFF")
            {
                digitalWrite(gpio_pin_HEAT, HIGH);
                logFile << "######## heater set OFF #######"  <<"\t\t";
                printTime(logFile);
                stateHeater = "OFF";
                fileStateHeat.open("/home/khadas/aqua/for_web/state_heat", std::ios::out);
                fileStateHeat <<"OFF     ";
                printTime(fileStateHeat);
                fileStateHeat.close();
            }
            if (temperature < min_temp && stateHeater != "ON")
            {
                digitalWrite(gpio_pin_HEAT, LOW);
                logFile << "######## heater set ON ########"  <<"\t\t";
                printTime(logFile);
                stateHeater = "ON";
                fileStateHeat.open("/home/khadas/aqua/for_web/state_heat", std::ios::out);
                fileStateHeat <<"ON     ";
                printTime(fileStateHeat);
                fileStateHeat.close();
            }
        }
        logFile.close();
        Mut.unlock();
        this_thread::sleep_for(chrono::milliseconds(1080));
    }
}

void feed()
{
    digitalWrite(gpio_pin_PUMP_AIR, HIGH);
    this_thread::sleep_for(chrono::milliseconds(20000));
    digitalWrite(gpio_pin_FOOD, LOW);
    this_thread::sleep_for(chrono::milliseconds(long_food));
    digitalWrite(gpio_pin_FOOD, HIGH);
    logFile << "######## FOOD ON ########"  <<"\t\t";
    printTime(logFile);
    this_thread::sleep_for(chrono::milliseconds(300000));
    digitalWrite(gpio_pin_PUMP_AIR, LOW);
}


void
handlerFood()
{
    digitalWrite(gpio_pin_FOOD, HIGH);
    digitalWrite(gpio_pin_PUMP_AIR, LOW);
    this_thread::sleep_for(chrono::milliseconds(5000));
    Mut.lock();
    logFile.open("/home/khadas/aqua/logFile", std::ios::app); // окрываем файл для дозаписи
    logFile << "######## PUMP and AIR ON ########"  <<"\t";
    printTime(logFile);
    logFile.close();
    Mut.unlock();

    while(1)
    {

        Mut.lock();
        logFile.open("/home/khadas/aqua/logFile", std::ios::app); // окрываем файл для дозаписи

        auto timeNow = QTime::currentTime();
        for (int i = 0; i< food.size();++i)
        {
            QTime food_end = food[i];
            food_end = food_end.addSecs(60);
            if ((timeNow > food[i]) && (timeNow < food_end))
            {
                feed();
                if (i == 0)
                {
                    fileStateFeed.open("/home/khadas/aqua/for_web/state_food", std::ios::out);
                    printOnylTime(fileStateFeed);
                    fileStateFeed <<"   ";
                }
                else
                {
                    fileStateFeed.open("/home/khadas/aqua/for_web/state_food", std::ios::app);
                    printOnylTime(fileStateFeed);
                    fileStateFeed <<"   ";
                }
                fileStateFeed.close();
            }
        }

        logFile.close();
        Mut.unlock();
        this_thread::sleep_for(chrono::milliseconds(5000));
    }
}

int main () 
{
	if(-1 == wiringPiSetup())
	{
		printf("set up error");
		exit(1);
	}
//    system("gpio readall");
    pinMode(gpio_pin_UF, OUTPUT);
	pinMode(gpio_pin_COLD, OUTPUT);
	pinMode(gpio_pin_LAMP, OUTPUT);
	pinMode(gpio_pin_HEAT, OUTPUT);
    pinMode(gpio_pin_PUMP_AIR, OUTPUT);
	pinMode(gpio_pin_FOOD, OUTPUT);
    pinMode(gpio_pin_REZERV, OUTPUT);
	
    this_thread::sleep_for(chrono::milliseconds(3000));
    thread (receiveTemp, ref(temperature)).detach();
    thread (receiveSettings,
            ref(min_temp),
            ref(max_temp),
            ref(heater),
            ref(time_light_on),
            ref(time_light_off),
            ref(light),
            ref(time_UF_on),
            ref(time_UF_off),
            ref(UF)
            ).detach();
    thread (handlerLight, ref(light), ref(time_light_on), ref(time_light_off)).detach();
    thread (handlerUF, ref(UF), ref(time_UF_on), ref(time_UF_off)).detach();
    thread (handlerHeater, ref(heater), ref(min_temp), ref(max_temp)).detach();

    this_thread::sleep_for(chrono::milliseconds(3000));

    thread (handlerFood).detach();

    float temperatureForLog, temperatureForWeb, min_tempNew, max_tempNew;
    bool heaterNew = false;
    QTime time_light_on_New, time_light_off_New;
    bool lightNew = false;
    QTime time_UF_on_New, time_UF_off_New;
    bool UFNew = false;
    QString food_timeNew;

	while(1)
	{
        Mut.lock();
        logFile.open("/home/khadas/aqua/logFile", std::ios::app);

        if (abs(temperatureForLog - temperature) > 0.1)
        {
            logFile << "temp = " << temperature <<"\t\t\t\t";
            printTime(logFile);
            temperatureForLog = temperature;
        }
        if (temperatureForWeb != temperature)
        {
            fileTemperature.open("/home/khadas/aqua/for_web/temperature", std::ios::out);
            fileTemperature <<  temperature <<" °C    ";
            printTime(fileTemperature);
            temperatureForWeb = temperature;
            fileTemperature.close();
        }
        if (min_tempNew != min_temp)
        {
            logFile << "settig_min_temp = " << min_temp <<"\t\t\t";
            printTime(logFile);
            min_tempNew = min_temp;
            fileHeat_on.open("/home/khadas/aqua/for_web/heat_on", std::ios::out);
            fileHeat_on<<min_tempNew<<" °C";
            fileHeat_on.close();
        }
        if (max_tempNew != max_temp)
        {
            logFile << "settig_max_temp = " << max_temp <<"\t\t\t";
            printTime(logFile);
            max_tempNew = max_temp;
            fileHeat_off.open("/home/khadas/aqua/for_web/heat_off", std::ios::out);
            fileHeat_off<<max_tempNew<<" °C";
            fileHeat_off.close();
        }
        if (heaterNew != heater)
        {
            logFile << "settig_heater = " << boolalpha <<heater<<"\t\t\t";
            printTime(logFile);
            heaterNew = heater;
        }

        if (time_light_on_New != time_light_on)
        {
            logFile << "settig_light_on = " << time_light_on.toString("hh:mm").toStdString()<<"\t\t\t";
            printTime(logFile);
            time_light_on_New = time_light_on;
            fileLight_on.open("/home/khadas/aqua/for_web/light_on", std::ios::out);
            fileLight_on<<time_light_on_New.toString().toStdString();
            fileLight_on.close();
        }
        if (time_light_off_New != time_light_off)
        {
            logFile << "settig_light_off = " << time_light_off.toString("hh:mm").toStdString()<<"\t\t";
            printTime(logFile);
            time_light_off_New = time_light_off;
            fileLight_off.open("/home/khadas/aqua/for_web/light_off", std::ios::out);
            fileLight_off<<time_light_off_New.toString().toStdString();
            fileLight_off.close();
        }
        if (lightNew != light)
        {
            logFile << "settig_light = " << boolalpha <<light<<"\t\t\t";
            printTime(logFile);
            lightNew = light;
        }

        if (time_UF_on_New != time_UF_on)
        {
            logFile << "settig_UF_on = " << time_UF_on.toString("hh:mm").toStdString()<<"\t\t\t";
            printTime(logFile);
            time_UF_on_New = time_UF_on;
        }
        if (time_UF_off_New != time_UF_off)
        {
            logFile << "settig_UF_off = " << time_UF_off.toString("hh:mm").toStdString()<<"\t\t\t";
            printTime(logFile);
            time_UF_off_New = time_UF_off;
        }
        if (UFNew != UF)
        {
            logFile << "settig_UF = " << boolalpha <<UF<<"\t\t\t";
            printTime(logFile);
            UFNew = UF;
        }

        if (food_timeNew != food_time)
        {
            logFile << "settig_food_time = " << food_time.toStdString()<<"\t\t\t";
            printTime(logFile);
            food_timeNew = food_time;
            fileFood.open("/home/khadas/aqua/for_web/food_time", std::ios::out);
            fileFood<<food_time.toStdString();
            fileFood.close();
        }

        logFile.close();
        Mut.unlock();

        this_thread::sleep_for(chrono::milliseconds(5000));

	}
    
    
    return 0;

} 
