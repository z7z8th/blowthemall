/*
  Copyright © 2012  Vinícius dos Santos Oliveira

  This file is part of libbta.

  libbta is free software: you can redistribute it and/or modify
  it under the terms of the GNU Lesser General Public License as published
  by the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
  */

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
