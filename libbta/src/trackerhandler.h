#ifndef LIBBTA_TRACKER_HANDLER_H
#define LIBBTA_TRACKER_HANDLER_H

#include "libbta_global.h"
#include <QtCore/QObject>
#include <QtCore/QVariantMap>

namespace libbta {
namespace Tracker {

class LIBBTA_EXPORT Handler : public QObject
{
    Q_OBJECT
public:
    explicit Handler(QObject *parent = 0);

//    // Usefull methods for game servers:
//    Q_INVOKABLE void publish(const QString &gameId, const QHostAddress &address,
//                             quint16 port, const QVariantMap &options);

//    Q_INVOKABLE void unpublish(const QHostAddress &address, quint16 port);

//    Q_INVOKABLE int publishTimeout();


//    // Usefull method for game clients:
//    Q_INVOKABLE QVariantMap listFirst(const QString &gameId,
//                                      const QVariantMap &options);

//    Q_INVOKABLE QVariantMap list(const QString &gameId,
//                                 const QVariantMap &options,
//                                 const QVariant &offset);

//    Q_INVOKABLE void verify(const QHostAddress &address, quint16 port);
};

} // namespace Tracker
} // namespace libbta

#endif // LIBBTA_TRACKER_HANDLER_H
