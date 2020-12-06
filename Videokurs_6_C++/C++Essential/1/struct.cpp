#include <iostream>
#include <string>

using namespace std;

typedef unsigned int uint;
enum class Color : long long;

void foo(Color a);

enum class Color : long long {red = -300000000000000, yellow = -3, green = 0, blue};

struct Glass
{
    string type;//24
};

struct Door
{
    Glass glass;//24
    double width;//8
    double length;//8
};

struct Car
{
    int wheels : 16;//4
    int length : 16;//4
    int width : 16;//4
    uint seats : 16;//4
    int for_bool : 31;
    bool a : 1;
    int q;
    string name;//24
    Door door;//40
//    struct SteeringWheel
//    {
//        string type; //24
//    };
} other_car;

int main()
{
    int array[10];

    double d;

    Car my_car;
    //Car::SteeringWheel wheel;

    my_car.door.glass.type;
    my_car.name = "The best car";
    my_car.length = 100;

    cout << sizeof(Glass) << "\n";
    cout << sizeof(Door) << "\n";
    cout << sizeof(Car) << "\n";
    //cout << sizeof(Car::SteeringWheel) << "\n";

    cout << my_car.name << " ,length = " << my_car.length << ", width = " << my_car.width << " wheels = " << my_car.wheels;

    return 0;
}
