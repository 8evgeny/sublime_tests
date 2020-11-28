// Фасад (Facade)

#include <iostream>

class VideoControl
{
public:
    void info() {};
    void alert() {};
};

class Database
{
public:
    void create() {};
    void update() {};
};

class Printer
{
public:
    void print() {};
};

class Fiscal
{
public:
    void report() {};
};

class Register
{
    VideoControl vc;
    Database db;
    Printer printer;
    Fiscal f;

public:
    void sale_doc()
    {
        db.create();
        vc.info();
        printer.print();
        f.report();
    };

    void ret_doc()
    {
        db.update();
        vc.alert();
        printer.print();
        f.report();
    };
};

int main(int, char *[])
{
    Register r;

    r.sale_doc();
    r.ret_doc();
}
