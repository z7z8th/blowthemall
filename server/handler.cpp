#include "handler.h"

Handler::Handler(QObject *parent) :
    QObject(parent)
{
}

int Handler::publishTimeout()
{
    return 2;
}
