/*
  Copyright © 2011  Vinícius dos Santos Oliveira

  This file is part of Phobos-RPC.

  Phobos-RPC is free software: you can redistribute it and/or modify
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

#ifndef PHOBOSRPC_PEER_H
#define PHOBOSRPC_PEER_H

#include "phobosrpc_global.h"
#include <QObject>
#include <QVariant>
#include <QSharedPointer>

namespace Phobos {

class ResponseHandler;

class PHOBOSRPC_EXPORT Peer: public QObject
{
    Q_OBJECT
public:
    Peer(QObject *parent = NULL);

signals:
    void readyRequest(QSharedPointer<Phobos::ResponseHandler> handler);
    void readyRequestMessage(QByteArray json);

    void readyResponse(QVariant result, QVariant id);
    void readyResponseMessage(QByteArray json);

    void requestError(int code, QString message, QVariant data);

public slots:
    void handleMessage(const QByteArray &json);
    void handleRequest(const QVariant &json);
    void handleResponse(const QVariant &json);

    void reply(const QVariant &json);

    bool call(const QString &method, const QVariant &params, const QVariant &id);
};

} // namespace Phobos

#endif // PHOBOSRPC_PEER_H
