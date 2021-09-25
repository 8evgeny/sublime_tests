#include "italictext.h"

ItalicText::ItalicText(QObject *parent) : Text(parent)
{

}


void ItalicText::process(QString &input)
{
    Text::process(input);
    input.insert(0,"<i>");
    input.append("</i>");
}
