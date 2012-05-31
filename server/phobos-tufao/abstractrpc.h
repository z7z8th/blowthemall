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
#ifndef ABSTRACTRPC_H
#define ABSTRACTRPC_H

#include <QObject>
#include <Tufao/AbstractMessageSocket>

class AbstractRpc : public QObject
{
    Q_OBJECT
public:
    explicit AbstractRpc(QObject *handler,
                         Tufao::AbstractMessageSocket *messagesLayer,
                         QObject *parent = 0);

    void setMessagesLayer(Tufao::AbstractMessageSocket *socket);
    Tufao::AbstractMessageSocket *messagesLayer();

    void setHandler(QObject *object);
    QObject *handler();

signals:
    void messagesLayerChanged(Tufao::AbstractMessageSocket *newSocket,
                              Tufao::AbstractMessageSocket *oldSocket);
    void handlerChanged(QObject *newObject, QObject *oldObject);

protected:
    QObject *handler_;
    Tufao::AbstractMessageSocket *socket_;
};

#endif // ABSTRACTRPC_H
