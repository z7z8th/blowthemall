#include "handler.h"
#include "tracker.h"

Handler::Handler(QObject *parent) :
    QObject(parent),
    tracker(Tracker::instance())
{
}

int Handler::publishTimeout()
{
    return tracker.publishTimeout();
}
