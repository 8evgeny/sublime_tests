#include "boldtext.h"

BoldText::BoldText(QObject *parent) : Text(parent)
{

}


void BoldText::process(QString &input)
{
    Text::process(input);
    input.insert(0,"<b>");
    input.append("</b>");
}
