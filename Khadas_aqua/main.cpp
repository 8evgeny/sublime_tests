#include <iostream>
#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <thread>
#include <iomanip>
#include <chrono>
#include <QtCore>
#include <QDebug>

using namespace std;

const int gpio_pin_RESERV = 6; 	//PIN22
const int gpio_pin_COLD = 	7; 	//PIN23
const int gpio_pin_LAMP = 	10;	//PIN29
const int gpio_pin_HEAT = 	11;	//PIN30
const int gpio_pin_PUMP = 	12;	//PIN31
const int gpio_pin_AIR  = 	13;	//PIN32
const int gpio_pin_FOOD =	15;	//PIN35
int min_temp;
int max_temp;
QString time_on;
QString time_off;
								//PIN37   onewire  измерение температуры
								//PIN40   GND
								//PIN1    +5
								//PIN2    +5

float temperature;


void receiveTemp(float & temperature)
{
    float temperatureOld;
    float temperatureNew;
    while(1)
    {
        std::string tmp;
    //    float temp;
        const char *cmd = "./tempread.sh";
        char buf[BUFSIZ];
        FILE *ptr;
        if ((ptr = popen(cmd, "r")) != NULL)
        {
            while(fgets(buf, BUFSIZ, ptr) != NULL);
    //                (void) printf("%s", buf);
            std::string tmp2{buf};
            tmp = tmp2;
            (void) pclose(ptr);
        }
        temperature = std::stof(tmp);
        this_thread::sleep_for(chrono::milliseconds(10000));
    }
}



int main () 
{
//    QSettings settings(configPath, QSettings::IniFormat);
//        settings.beginGroup("/General");
//        settings.setValue("/InterviewPath", interviewPath);
//        settings.endGroup();
//QSettings settings("folderName", "fileName");

    QSettings settings("config", QSettings::IniFormat);
    settings.beginGroup("Temperature");
    min_temp = settings.value( "min_temp").toFloat();
    max_temp = settings.value( "max_temp").toFloat();
    settings.endGroup();

    settings.beginGroup("Light");
//    settings.setValue("time", curr);
    time_on = settings.value( "time_on").toString();
    time_off = settings.value( "time_off").toString();
    settings.endGroup();

    qDebug()<<"min_temp ="<<min_temp<<"\tmax_temp ="<<max_temp;
    qDebug()<<"time_on ="<<time_on<<"\ttime_off ="<<time_off;


	if(-1 == wiringPiSetup())
	{
		printf("set up error");
		exit(1);
	}
//    system("gpio readall");
	pinMode(gpio_pin_RESERV, OUTPUT);
	pinMode(gpio_pin_COLD, OUTPUT);
	pinMode(gpio_pin_LAMP, OUTPUT);
	pinMode(gpio_pin_HEAT, OUTPUT);
	pinMode(gpio_pin_PUMP, OUTPUT);
	pinMode(gpio_pin_AIR, OUTPUT);
	pinMode(gpio_pin_FOOD, OUTPUT);
	
//	std::cout <<"gpio init...\n"<<std::endl;
//	system("gpio readall");

    std::thread (receiveTemp, ref(temperature)).detach();



    this_thread::sleep_for(chrono::milliseconds(3000));

    float temperatureNew;
	while(1)
	{

        if (temperatureNew != temperature)
        {
            std::cout << "temp=" << temperature <<"\t\t";
            const auto now = std::chrono::system_clock::now();
            const auto t_c = std::chrono::system_clock::to_time_t(now);
            std::cout << std::put_time(std::localtime(&t_c), "%T  %d.%b.%y \n");
            temperatureNew = temperature;
        }

        this_thread::sleep_for(chrono::milliseconds(60000));






//		digitalWrite(gpio_pin_RESERV, HIGH);
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

//		digitalWrite(gpio_pin_RESERV, LOW);
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
