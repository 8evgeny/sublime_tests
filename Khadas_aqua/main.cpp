#include <iostream>
#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <thread>
#include <iomanip>
#include <chrono>
#include <QtCore>

using namespace std;

const int gpio_pin_RESERV = 6; 	//PIN22
const int gpio_pin_COLD = 	7; 	//PIN23
const int gpio_pin_LAMP = 	10;	//PIN29
const int gpio_pin_HEAT = 	11;	//PIN30
const int gpio_pin_PUMP = 	12;	//PIN31
const int gpio_pin_AIR  = 	13;	//PIN32
const int gpio_pin_FOOD =	15;	//PIN35


								//PIN37   onewire  измерение температуры
								//PIN40   GND
								//PIN1    +5
								//PIN2    +5


void receiveTemp()
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
        temperatureNew = std::stof(tmp);
        if (temperatureNew != temperatureOld)
        {
            std::cout << "new temp=" << temperatureNew <<"\t\t";
            const auto now = std::chrono::system_clock::now();
            const auto t_c = std::chrono::system_clock::to_time_t(now);
            std::cout << std::put_time(std::localtime(&t_c), "%T %d.%b.%y \n");
            temperatureOld = temperatureNew;
        }
        delay(60000);
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
    int min_temp = settings.value( "min_temp").toFloat();
    int max_temp = settings.value( "max_temp").toFloat();
    settings.endGroup();

    cout<<"min_temp="<<min_temp<<"\tmax_temp="<<max_temp<<endl;



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

    std::thread tt(receiveTemp);
    tt.detach();

	while(1)
	{
    delay(60000);
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
