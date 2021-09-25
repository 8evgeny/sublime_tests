#include "text.h"

Text::Text(QObject *parent) : QObject(parent)
{

}

void Text::process(QString &input)
{
    if(parent())
    {
        Text *text= qobject_cast<Text*>(parent());
        if(text) text->process(input);
    }
}
