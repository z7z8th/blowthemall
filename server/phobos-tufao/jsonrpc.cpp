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
#include "jsonrpc.h"
#include "phobos/utils.h"

JsonRpc::JsonRpc(QObject *handler,
                 Tufao::AbstractMessageSocket *messagesLayer,
                 QObject *parent) :
    AbstractRpc(handler, messagesLayer, parent),
    peer(new Phobos::Peer(this)),
    server(new Phobos::Server(this))
{
    server->connectToObject(peer);
    if (handler_)
        server->setObject(handler_);

    // logic
    connect(peer, SIGNAL(readyResponse(QVariant,QVariant)),
            this, SLOT(onReadyResponse(QVariant,QVariant)));
    connect(peer, SIGNAL(requestError(int,QString,QVariant,QVariant)),
            this, SLOT(onRequestError(int,QString,QVariant,QVariant)));

    // data stream
    connect(peer, SIGNAL(readyResponseMessage(QByteArray)),
            this, SLOT(onReadyMessage(QByteArray)));
    connect(peer, SIGNAL(readyRequestMessage(QByteArray)),
            this, SLOT(onReadyMessage(QByteArray)));

    if (socket_) {
        connect(socket_, SIGNAL(newMessage(QByteArray)),
                this, SLOT(onNewMessage(QByteArray)));
    }

    // state changes
    connect(this, SIGNAL(messagesLayerChanged(Tufao::AbstractMessageSocket*,Tufao::AbstractMessageSocket*)),
            this, SLOT(onMessagesLayerChanged(Tufao::AbstractMessageSocket*,Tufao::AbstractMessageSocket*)));
    connect(this, SIGNAL(handlerChanged(QObject*,QObject*)),
            this, SLOT(onHandlerChanged(QObject*,QObject*)));
}

bool JsonRpc::callWith(QObject *receiver, QMetaMethod method,
                       const QString &remoteMethod, const QVariant &arg0,
                       const QVariant &arg1, const QVariant &arg2,
                       const QVariant &arg3, const QVariant &arg4,
                       const QVariant &arg5, const QVariant &arg6,
                       const QVariant &arg7, const QVariant &arg8,
                       const QVariant &arg9)
{
    int i = findIndex();
    if (i == -1)
        return false;

    calls[i] = qMakePair(receiver, method);
    peer->call(remoteMethod, Phobos::createParams(arg0, arg1, arg2, arg3, arg4,
                                                  arg5, arg6, arg7, arg8, arg9),
               QVariant(i));
    return true;
}

bool JsonRpc::callWith(QObject *receiver, const char *method,
                       const QString &remoteMethod, const QVariant &arg0,
                       const QVariant &arg1, const QVariant &arg2,
                       const QVariant &arg3, const QVariant &arg4,
                       const QVariant &arg5, const QVariant &arg6,
                       const QVariant &arg7, const QVariant &arg8,
                       const QVariant &arg9)
{
    int i = receiver->metaObject()->indexOfMethod(method);
    if (i == -1)
        return false;

    return callWith(receiver, receiver->metaObject()->method(i), remoteMethod,
                    arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
}

void JsonRpc::onReadyResponse(const QVariant &result, const QVariant &id)
{
    const int key(id.toInt());
    if (!calls.contains(key))
        return;

    QMetaMethod method(calls[key].second);
    Phobos::ArgumentsHandler argsHandler;
    QVariantList params;
    params.push_back(result);
    QVector<QGenericArgument> args = argsHandler.convert(params);
    method.invoke(calls[key].first, Qt::DirectConnection, args[0]);
}

void JsonRpc::onRequestError(int code, const QString &message,
                             const QVariant &data, const QVariant &id)
{
    calls.remove(id.toInt());
    emit requestError(code, message, data);
}

void JsonRpc::onReadyMessage(const QByteArray &json)
{
    if (socket_)
        socket_->sendMessage(json);
}

void JsonRpc::onNewMessage(const QByteArray &msg)
{
    peer->handleMessage(msg);
}

void JsonRpc::onMessagesLayerChanged(Tufao::AbstractMessageSocket *newSocket,
                                     Tufao::AbstractMessageSocket *oldSocket)
{
    if (oldSocket) {
        disconnect(oldSocket, SIGNAL(newMessage(QByteArray)),
                   this, SLOT(onNewMessage(QByteArray)));
    }
    if (newSocket) {
        connect(newSocket, SIGNAL(newMessage(QByteArray)),
                this, SLOT(onNewMessage(QByteArray)));
    }
}

void JsonRpc::onHandlerChanged(QObject *newHandler, QObject *oldHandler)
{
    Q_UNUSED(oldHandler)

    server->setObject(newHandler);
}

int JsonRpc::findIndex()
{
    int i(0);
    for (;i >= 0;++i) {
        if (!calls.contains(i))
            break;
    }

    if (i < 0)
        return -1;

    return i;
}
