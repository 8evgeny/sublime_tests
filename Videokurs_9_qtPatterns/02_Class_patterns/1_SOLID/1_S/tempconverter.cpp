#include "tempconverter.h"

TempConverter::TempConverter(QObject* parent)
    : QObject(parent)
{
}

int TempConverter::celciusToFarengeit(int val)
{
    auto o = (val * 9.0) / 5.0 + 32;
    return o;
}

int TempConverter::farengeiyToCelcius(int val)
{
    auto o = (val - 32) * 5.0 / 9.0;
    return o;
}
