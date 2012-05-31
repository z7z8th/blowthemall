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
#include "abstractrpc.h"

AbstractRpc::AbstractRpc(QObject *handler,
                         Tufao::AbstractMessageSocket *messagesLayer,
                         QObject *parent) :
    QObject(parent),
    handler_(handler),
    socket_(messagesLayer)
{
}

void AbstractRpc::setMessagesLayer(Tufao::AbstractMessageSocket *socket)
{
    if (socket == socket_)
        return;

    Tufao::AbstractMessageSocket *const oldSocket = socket_;
    socket_ = socket;
    emit messagesLayerChanged(socket_, oldSocket);
}

Tufao::AbstractMessageSocket *AbstractRpc::messagesLayer()
{
    return socket_;
}

void AbstractRpc::setHandler(QObject *object)
{
    if (handler_ == object)
        return;

    QObject *const oldHandler = handler_;
    handler_ = object;
    emit handlerChanged(handler_, oldHandler);
}
