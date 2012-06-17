#ifndef TRACKER_H
#define TRACKER_H

#include <QtCore/QObject>
#include <QtCore/QVariantMap>

#include <QtNetwork/QHostAddress>

class Tracker : public QObject
{
    Q_OBJECT
public:
    static Tracker &instance();

    // Usefull methods for game servers:
    void publish(const QString &gameId, const QHostAddress &address,
                 quint16 port, const QVariantMap &options);

    void unpublish(const QHostAddress &address, quint16 port);

    int publishTimeout();


    // Usefull method for game clients:
    QVariantMap listFirst(const QString &gameId, const QVariantMap &options);

    QVariantMap list(const QString &gameId, const QVariantMap &options,
                     const QVariant &offset);

    void verify(const QHostAddress &address, quint16 port);

private:
    explicit Tracker();
};

#endif // TRACKER_H
