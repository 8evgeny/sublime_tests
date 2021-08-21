#include "mainwiget.h"
#include <iostream>

MainWiget::MainWiget(QWidget *parent) : QWidget(parent)
{

}

void MainWiget::print()
{
    std::cout <<"test"<<std::endl;
}
