#include "basestate.h"

BaseState::BaseState(QObject *parent) :
    QObject(parent)
{
}

QString BaseState::protocol_version()
{
    static QString version("0.1");
    qDebug("called");
    return version;
}
