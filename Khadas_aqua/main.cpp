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

const int gpio_pin_UF = 6; 	//PIN22
const int gpio_pin_COLD = 	7; 	//PIN23
const int gpio_pin_LAMP = 	10;	//PIN29
const int gpio_pin_HEAT = 	11;	//PIN30
const int gpio_pin_PUMP = 	12;	//PIN31
const int gpio_pin_AIR  = 	13;	//PIN32
const int gpio_pin_FOOD =	15;	//PIN35

float min_temp, max_temp;
bool heater = false;
float temperature;
QTime time_light_on, time_light_off;
QTime food1, food2, food3, long_food;
bool light = true;
mutex Mut;
ofstream out;          // поток для записи
constexpr long numLinesInLog = 250;

								//PIN37   onewire  измерение температуры
								//PIN40   GND
								//PIN1    +5
								//PIN2    +5


void changePosWriteInLog()
{
//    while(1)
//    {
//        Mut.lock();
//        out.open("/home/khadas/aqua/logFile", std::ios::app);
////        out<<" ";
//        if( auto pos = out.tellp() > 250)
//        {
//            out.seekp(pos - numLinesInLog);
//            out<<"********************************************"<<endl;
//        }
//        out.close();
//        Mut.unlock();
//        this_thread::sleep_for(chrono::milliseconds(60000));
//    }
}

void printTime()
{
    const auto now = std::chrono::system_clock::now();
    const auto t_c = std::chrono::system_clock::to_time_t(now);
    std::cout << std::put_time(std::localtime(&t_c), "%T  %d.%b.%y \n");
    out << std::put_time(std::localtime(&t_c), "%T  %d.%b.%y \n");
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
receiveSettings(float & min_temp, float & max_temp, bool & heater, QTime & time_light_on, QTime & time_light_off, bool & light)
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

        settings.beginGroup("Food");
        foodTimes = settings.value( "time_Food").toStringList();
        food1 = QTime::fromString(foodTimes.at(0));
        food2 = QTime::fromString(foodTimes.at(1));
        food3 = QTime::fromString(foodTimes.at(2));
        long_food = QTime::fromString(settings.value( "long_Food").toString());
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
        out.open("/home/khadas/aqua/logFile", std::ios::app);
        if (!light)
        {
            digitalWrite(gpio_pin_LAMP, LOW);
            if (stateLight != "OFF")
            {
                std::cout << "######## light set OFF #######" <<"\t\t";
                out << "######## light set OFF #######" <<"\t\t";
                printTime();
                stateLight = "OFF";
            }
        }
        if (light)
        {
            auto timeNow = QTime::currentTime();
            if ((timeNow > time_light_on) && (timeNow < time_light_off) && (stateLight != "ON"))
            {
                digitalWrite(gpio_pin_LAMP, HIGH);
                std::cout << "######## light set ON ########"  <<"\t\t";
                out << "######## light set ON ########"  <<"\t\t";
                printTime();
                stateLight = "ON";
            }
            if (!((timeNow > time_light_on) && (timeNow < time_light_off)) && (stateLight != "OFF"))
            {
                digitalWrite(gpio_pin_LAMP, LOW);
                std::cout << "######## light set OFF ########"  <<"\t\t";
                out << "######## light set OFF ########"  <<"\t\t";
                printTime();
                stateLight = "OFF";
            }
        }
        out.close();
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
        out.open("/home/khadas/aqua/logFile", std::ios::app); // окрываем файл для дозаписи
        if (!heater && stateHeater != "OFF")
        {
            digitalWrite(gpio_pin_HEAT, LOW);
            std::cout << "######## heater set OFF #######" <<"\t\t";
            out << "######## heater set OFF #######" <<"\t\t";
            printTime();
            stateHeater = "OFF";
        }
        if (heater)
        {
            if (temperature > max_temp && stateHeater != "OFF")
            {
                digitalWrite(gpio_pin_HEAT, LOW);
                std::cout << "######## heater set OFF #######"  <<"\t\t";
                out << "######## heater set OFF #######"  <<"\t\t";
                printTime();
                stateHeater = "OFF";
            }
            if (temperature < min_temp && stateHeater != "ON")
            {
                digitalWrite(gpio_pin_HEAT, HIGH);
                std::cout << "######## heater set ON ########"  <<"\t\t";
                out << "######## heater set ON ########"  <<"\t\t";
                printTime();
                stateHeater = "ON";
            }
        }
        out.close();
        Mut.unlock();
        this_thread::sleep_for(chrono::milliseconds(1080));
    }
}

void
handlerFood()
{
    string stateFood = "none";
    while(1)
    {
        Mut.lock();
        out.open("/home/khadas/aqua/logFile", std::ios::app); // окрываем файл для дозаписи
//        if (temperature > max_temp && stateFood != "OFF")
//        {
//            digitalWrite(gpio_pin_HEAT, LOW);
//            std::cout << "######## heater set OFF #######"  <<"\t\t";
//            out << "######## heater set OFF #######"  <<"\t\t";
//            printTime();
//            stateFood = "OFF";
//        }
//        if (1)
//        {
//            digitalWrite(gpio_pin_HEAT, HIGH);
//            std::cout << "######## heater set ON ########"  <<"\t\t";
//            out << "######## heater set ON ########"  <<"\t\t";
//            printTime();
//            stateFood = "ON";
//        }
        out.close();
        Mut.unlock();
        this_thread::sleep_for(chrono::milliseconds(1080));
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
	pinMode(gpio_pin_PUMP, OUTPUT);
	pinMode(gpio_pin_AIR, OUTPUT);
	pinMode(gpio_pin_FOOD, OUTPUT);
	
//	std::cout <<"gpio init...\n"<<std::endl;
//	system("gpio readall");

//    thread (changePosWriteInLog).detach();
    this_thread::sleep_for(chrono::milliseconds(3000));
    thread (receiveTemp, ref(temperature)).detach();
    thread (receiveSettings,
            ref(min_temp),
            ref(max_temp),
            ref(heater),
            ref(time_light_on),
            ref(time_light_off),
            ref(light)
            ).detach();
    thread (handlerLight, ref(light), ref(time_light_on), ref(time_light_off)).detach();
    thread (handlerHeater, ref(heater), ref(min_temp), ref(max_temp)).detach();

    this_thread::sleep_for(chrono::milliseconds(3000));

    float temperatureNew, min_tempNew, max_tempNew;
    bool heaterNew = false;
    QTime time_light_on_New, time_light_off_New;
    bool lightNew = false;

	while(1)
	{
        Mut.lock();
        out.open("/home/khadas/aqua/logFile", std::ios::app);
        if (abs(temperatureNew - temperature) > 0.1)
        {
            std::cout << "temp = " << temperature <<"\t\t\t\t";
            out << "temp = " << temperature <<"\t\t\t\t";
            printTime();
            temperatureNew = temperature;
        }
        if (min_tempNew != min_temp)
        {
            std::cout << "settig_min_temp = " << min_temp <<"\t\t\t";
            out << "settig_min_temp = " << min_temp <<"\t\t\t";
            printTime();
            min_tempNew = min_temp;
        }
        if (max_tempNew != max_temp)
        {
            std::cout << "settig_max_temp = " << max_temp <<"\t\t\t";
            out << "settig_max_temp = " << max_temp <<"\t\t\t";
            printTime();
            max_tempNew = max_temp;
        }
        if (heaterNew != heater)
        {
            std::cout << "settig_heater = " << boolalpha <<heater<<"\t\t\t";
            out << "settig_heater = " << boolalpha <<heater<<"\t\t\t";
            printTime();
            heaterNew = heater;
        }
        if (time_light_on_New != time_light_on)
        {
            std::cout << "settig_light_on = " << time_light_on.toString("hh:mm").toStdString()<<"\t\t\t";
            out << "settig_light_on = " << time_light_on.toString("hh:mm").toStdString()<<"\t\t\t";
            printTime();
            time_light_on_New = time_light_on;
        }
        if (time_light_off_New != time_light_off)
        {
            std::cout << "settig_light_off = " << time_light_off.toString("hh:mm").toStdString()<<"\t\t";
            out << "settig_light_off = " << time_light_off.toString("hh:mm").toStdString()<<"\t\t";
            printTime();
            time_light_off_New = time_light_off;
        }
        if (lightNew != light)
        {
            std::cout << "settig_light = " << boolalpha <<light<<"\t\t\t\t";
            out << "settig_light = " << boolalpha <<light<<"\t\t\t";
            printTime();
            lightNew = light;
        }
        out.close();
        Mut.unlock();

        this_thread::sleep_for(chrono::milliseconds(5000));






//		digitalWrite(gpio_pin_UF, HIGH);
//		printf("PIN_22 ON\n");
//		delay(1000);
//		digitalWrite(gpio_pin_COLD, HIGH);
//		printf("PIN_23 ON\n");
//		delay(1000);
//		digitalWrite(gpio_pin_LAMP, HIGH);
//		printf("PIN_29 ON\n");
//		delay(1000);
//		digitalWrite(gpio_pin_HEAT, HIGH);
//		printf("PIN_30 ON\n");
//		delay(1000);
//		digitalWrite(gpio_pin_PUMP, HIGH);
//		printf("PIN_31 ON\n");
//		delay(1000);
//		digitalWrite(gpio_pin_LAMP, HIGH);
//		printf("PIN_32 ON\n");
//		delay(1000);
//		digitalWrite(gpio_pin_FOOD, HIGH);
//		printf("PIN_35 ON\n");
//		delay(1000);

//		digitalWrite(gpio_pin_UF, LOW);
//		printf("PIN_22 OFF\n");
//		delay(1000);
//		digitalWrite(gpio_pin_COLD, LOW);
//		printf("PIN_23 OFF\n");
//		delay(1000);
//		digitalWrite(gpio_pin_LAMP, LOW);
//		printf("PIN_29 OFF\n");
//		delay(1000);
//		digitalWrite(gpio_pin_HEAT, LOW);
//		printf("PIN_30 OFF\n");
//		delay(1000);
//		digitalWrite(gpio_pin_PUMP, LOW);
//		printf("PIN_31 OFF\n");
//		delay(1000);
//		digitalWrite(gpio_pin_LAMP, LOW);
//		printf("PIN_32 OFF\n");
//		delay(1000);
//		digitalWrite(gpio_pin_FOOD, LOW);
//		printf("PIN_35 OFF\n");
//		delay(1000);
	}
    
    
    return 0;

} 
