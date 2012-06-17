#include "tracker.h"

Tracker &Tracker::instance()
{
    static Tracker *tracker = new Tracker;
    return *tracker;
}

void Tracker::publish(const QString &gameId, const QHostAddress &address,
                      quint16 port, const QVariantMap &options)
{
    // TODO:
    //  * Add game room to the list
    //   * Only one game room can exist by address/ip
    //  * Remove the room from the list when it reachs timeout
}

void Tracker::unpublish(const QHostAddress &address, quint16 port)
{
    // TODO:
    // * Remove game room from list
}

int Tracker::publishTimeout()
{
    return 2;
}

QVariantMap Tracker::listFirst(const QString &gameId,
                               const QVariantMap &options)
{
    // TODO
}

QVariantMap Tracker::list(const QString &gameId, const QVariantMap &options,
                          const QVariant &offset)
{
    // TODO
}

void Tracker::verify(const QHostAddress &address, quint16 port)
{
    // TODO
}

Tracker::Tracker() :
    QObject(NULL)
{
}
