/*
  Copyright © 2012  Vinícius dos Santos Oliveira

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
#ifndef JSONRPC_H
#define JSONRPC_H

#include "abstractrpc.h"
#include "phobos/peer.h"
#include "phobos/server.h"
#include <QtCore/QMetaMethod>

class JsonRpc : public AbstractRpc
{
    Q_OBJECT
public:
    explicit JsonRpc(QObject *handler,
                     Tufao::AbstractMessageSocket *messagesLayer,
                     QObject *parent = 0);

    bool callWith(QObject *receiver, QMetaMethod method,
                  const QString &remoteMethod,
                  const QVariant &arg0 = QVariant(),
                  const QVariant &arg1 = QVariant(),
                  const QVariant &arg2 = QVariant(),
                  const QVariant &arg3 = QVariant(),
                  const QVariant &arg4 = QVariant(),
                  const QVariant &arg5 = QVariant(),
                  const QVariant &arg6 = QVariant(),
                  const QVariant &arg7 = QVariant(),
                  const QVariant &arg8 = QVariant(),
                  const QVariant &arg9 = QVariant());

    bool callWith(QObject *receiver, const char * method,
                  const QString &remoteMethod,
                  const QVariant &arg0 = QVariant(),
                  const QVariant &arg1 = QVariant(),
                  const QVariant &arg2 = QVariant(),
                  const QVariant &arg3 = QVariant(),
                  const QVariant &arg4 = QVariant(),
                  const QVariant &arg5 = QVariant(),
                  const QVariant &arg6 = QVariant(),
                  const QVariant &arg7 = QVariant(),
                  const QVariant &arg8 = QVariant(),
                  const QVariant &arg9 = QVariant());

signals:
    void requestError(int code, QString message, QVariant data);

private slots:
    void onReadyResponse(const QVariant &calls, const QVariant &id);
    void onRequestError(int code, const QString &message, const QVariant &data,
                        const QVariant &id);

    void onReadyMessage(const QByteArray &json);
    void onNewMessage(const QByteArray &msg);

    void onMessagesLayerChanged(Tufao::AbstractMessageSocket*newSocket,
                                Tufao::AbstractMessageSocket*oldSocket);
    void onHandlerChanged(QObject*newHandler, QObject*oldHandler);

private:
    int findIndex();

    Phobos::Peer *peer;
    Phobos::Server *server;
    QMap<int, QPair<QObject*,QMetaMethod> > calls;
};

#endif // JSONRPC_H
