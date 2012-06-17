#include "trackerhandler.h"
#include "tracker.h"

TrackerHandler::TrackerHandler(QObject *parent) :
    QObject(parent),
    tracker(Tracker::instance())
{
}

int TrackerHandler::publishTimeout()
{
    return tracker.publishTimeout();
}
