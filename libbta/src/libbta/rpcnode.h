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

#ifndef LIBBTA_RPC_RPCNODE_H
#define LIBBTA_RPC_RPCNODE_H

#include "libbta_global.h"

#include <QtCore/QObject>
#include <QtCore/QVariant>

#include <Tufao/AbstractMessageSocket>

#include <functional>

namespace libbta {
namespace Rpc {

class LIBBTA_EXPORT Node : public QObject
{
    Q_OBJECT
public:
    explicit Node(QObject *parent = 0);
    explicit Node(Tufao::AbstractMessageSocket *socket, QObject *parent = 0);
    ~Node();

    QObject *methods();
    void setMethods(QObject *object);

    Tufao::AbstractMessageSocket *messageSocket();
    void setMessageSocket(Tufao::AbstractMessageSocket *socket);

signals:
    void error(QVariant id, QByteArray data);

public slots:
    QVariant callWith(const QString &remoteMethod, const QVariantList &args,
                      std::function<void(QVariant)> receiver);
    QVariant callWith(const QString &remoteMethod, const QVariantMap &args,
                      std::function<void(QVariant)> receiver);

    void call(const QString &remoteMethod, const QVariantList &args);
    void call(const QString &remoteMethod, const QVariantMap &args);

private slots:
    void handleMessage(const QByteArray &msg);

private:
    enum Error
    {
        NO_ERROR,
        PARSE_ERROR      = -32700,
        INVALID_REQUEST  = -32600,
        METHOD_NOT_FOUND = -32601,
        INVALID_PARAMS   = -32602,
        INTERNAL_ERROR   = -32603
    };

    void handleRequest(const QVariant &object);
    void handleResponse(const QVariantMap &object);

    QVariantMap processRequest(const QVariantMap &request);
    QPair<QVariant, QVariantMap>
    processReply(const QString &method, const QVariant &args);

    struct Priv;
    Priv *priv;
};

} // namespace Rpc
} // namespace libbta

#endif // LIBBTA_RPC_RPCNODE_H
