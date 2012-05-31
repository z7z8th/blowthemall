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

#include "server.h"
#include "responsehandler.h"
#include "utils.h"

using namespace Phobos;

Server::Server(QObject *parent) :
    QObject(parent),
    m_object(NULL)
{
}

void Phobos::Server::setObject(QObject *object)
{
    m_object = object;
}

bool Phobos::Server::connectToObject(QObject *object)
{
    return connect(object,
                   SIGNAL(readyRequest(QSharedPointer<Phobos::ResponseHandler>)),
                   this,
                   SLOT(request(QSharedPointer<Phobos::ResponseHandler>)));
}

void Phobos::Server::disconnectFromObject(QObject *object)
{
    disconnect(object,
               SIGNAL(readyRequest(QSharedPointer<Phobos::ResponseHandler>)),
               this,
               SLOT(request(QSharedPointer<Phobos::ResponseHandler>)));
}

void Phobos::Server::request(QSharedPointer<Phobos::ResponseHandler> handler)
{
    if (!m_object) {
        handler->error(Error(ErrorCode::METHOD_NOT_FOUND));
        return;
    }

    QVariantList params = handler->params().toList();

    // 10 is the max number of args supported by moc/qobject/...
    if (params.size() > 10) {
        handler->error(Error(ErrorCode::INVALID_PARAMS));
        return;
    }

    const QMetaObject *metaObject = m_object->metaObject();

    int i = indexOfMethod(metaObject, handler->method(), params);

    if (i == -1) {
        handler->error(Error(ErrorCode::METHOD_NOT_FOUND));
        return;
    }

    QMetaMethod method = metaObject->method(i);
    QVariant result;

    {
        ArgumentsHandler argsHandler;
        QVector<QGenericArgument> args = argsHandler.convert(params);

        ReturnHandler retHandler;
        QGenericReturnArgument ret = retHandler.convert(method.typeName());

        method.invoke(m_object, Qt::DirectConnection, ret,
                      args[0], args[1], args[2], args[3], args[4],
                      args[5], args[6], args[7], args[8], args[9]);

        result = QVariant(retHandler);
    }

    handler->response(result);
}
