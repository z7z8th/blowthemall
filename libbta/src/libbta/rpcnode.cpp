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

#include "priv/rpcnode.h"
#include <qjson/parser.h>
#include <QDebug>
#include <iostream>

namespace libbta {
namespace Rpc {

Node::Node(QObject *parent) :
    QObject(parent),
    priv(new Priv)
{
}

Node::Node(Tufao::AbstractMessageSocket *socket, QObject *parent) :
    QObject(parent),
    priv(new Priv(socket))
{
    if (priv->socket)
        connect(priv->socket, SIGNAL(newMessage(QByteArray)),
                this, SLOT(handleMessage(QByteArray)));
}

Node::~Node()
{
    delete priv;
}

QObject *Node::methods()
{
    return priv->methods;
}

void Node::setMethods(QObject *object)
{
    priv->methods = object;
}

Tufao::AbstractMessageSocket *Node::messageSocket()
{
    return priv->socket;
}

void Node::setMessageSocket(Tufao::AbstractMessageSocket *socket)
{
    if (priv->socket)
        disconnect(priv->socket, SIGNAL(newMessage(QByteArray)),
                   this, SLOT(handleMessage(QByteArray)));

    priv->socket = socket;

    if (priv->socket)
        connect(priv->socket, SIGNAL(newMessage(QByteArray)),
                this, SLOT(handleMessage(QByteArray)));
}

QVariant Node::callWith(const QString &remoteMethod, const QVariantList &args,
                        std::function<void (QVariant)> receiver)
{
    return priv->callWith(remoteMethod, args, receiver);
}

QVariant Node::callWith(const QString &remoteMethod, const QVariantMap &args,
                        std::function<void (QVariant)> receiver)
{
    return priv->callWith(remoteMethod, args, receiver);
}

void Node::call(const QString &remoteMethod, const QVariantList &args)
{
    priv->call(remoteMethod, args);
}

void Node::call(const QString &remoteMethod, const QVariantMap &args)
{
    priv->call(remoteMethod, args);
}

void Node::handleMessage(const QByteArray &msg)
{
    QJson::Parser parser;

    bool ok;
    QVariant object = parser.parse(msg, &ok);

    if (!ok) {
        static QByteArray invalidJson = "{\"jsonrpc\": \"2.0\", \"error\": "
                "{\"code\": -32700, \"message\": \"Parse error\"}, "
                "\"id\": null}";
        priv->socket->sendMessage(invalidJson);
        return;
    }

    if (isRequestMessage(object)) {
        handleRequest(object);
    } else if (isResponseMessage(object)) {
        handleResponse(object.toMap());
    } else {
        static QByteArray invalidJsonRpc = "{\"jsonrpc\": \"2.0\", \"error\": "
                "{\"code\": -32600, \"message\": \"Invalid JSON-RPC.\"}, "
                "\"id\": null}";
        priv->socket->sendMessage(invalidJsonRpc);
    }
}

inline void Node::handleRequest(const QVariant &object)
{
    QVariant::Type type = object.type();
    if (type == QVariant::Map) {
        QVariantMap response = processRequest(object.toMap());
        if (!response.isEmpty())
            priv->socket->sendMessage(QJson::Serializer().serialize(response));
    } else if (type == QVariant::List) {
        QVariantList batch = object.toList();
        if (batch.isEmpty()) {
            priv->socket->sendMessage("{\"jsonrpc\": \"2.0\", \"error\": "
                                      "{\"code\": -32600, "
                                      "\"message\": \"Invalid JSON-RPC.\"}, "
                                      "\"id\": null}");
            return;
        }

        QVariantList response;
        for (const QVariant &i: batch) {
            QVariantMap singleResponse = processRequest(i.toMap());
            if (!singleResponse.isEmpty())
                response.push_back(singleResponse);
        }
        priv->socket->sendMessage(QJson::Serializer().serialize(response));
    } else {
        priv->socket->sendMessage("{\"jsonrpc\": \"2.0\", \"error\": "
                                  "{\"code\": -32600, "
                                  "\"message\": \"Invalid JSON-RPC.\"}, "
                                  "\"id\": null}");
    }
}

inline void Node::handleResponse(const QVariantMap &object)
{
    if (!object.contains("id"))
        return;

    if (object.contains("error")) {
        QVariant error = object["error"];
        if (error.type() != QVariant::Map)
            return;

        emit this->error(object["id"], QJson::Serializer().serialize(error));
        return;
    }

    QVariant key = object["id"];
    if (!object.contains("result") || !priv->calls.contains(key))
        return;

    priv->calls[key](object["result"]);
    priv->calls.remove(key);
}

QVariantMap Node::processRequest(const QVariantMap &request)
{
    qDebug() << "Entrou nos debugs !!!! GLoria!!" ;
	std::cout << "Foi !!! ?\n" << std::endl ;
    QVariantMap reply({{QString("jsonrpc"), QVariant("2.0")}});

    if (!request.contains("method")) {
        qDebug() << "1" ;
        reply["error"] = QVariantMap({{"code", -32600}, {"message", "Invalid Request."}});
        reply["id"] = QVariant();
        return reply;
    }

    QVariant method = request["method"];

    if (method.type() != QVariant::String) {
        qDebug() << "2" ;
                reply["error"] = QVariantMap({{"code", -32600}, {"message", "Invalid Request."}});
                reply["id"] = QVariant();
                return reply;
    }

    if (request.contains("params")) {
        QVariant params = request["params"];
        QVariant::Type paramsType = params.type();
        if (paramsType != QVariant::List
                && paramsType != QVariant::Map
                && !params.isNull()) {
        qDebug() << "3" ;
                    reply["error"] = QVariantMap({{"code", -32600}, {"message", "Invalid Request."}});
                    reply["id"] = QVariant();
                    return reply;
        }
    }

    if (request.contains("id")) {
        QVariant id = request["id"];
        QVariant::Type idType = id.type();
        if (idType != QVariant::String
                && idType != QVariant::Int
                && idType != QVariant::ULongLong
                && idType != QVariant::LongLong
                && idType != QVariant::Double
                && !id.isNull()) {
        qDebug() << "4" ;
            reply["error"] = QVariantMap({{"code", -32600}, {"message", "Invalid Request."}});
            reply["id"] = QVariant();
            return reply;
        }
        reply["id"] = id;
    }

    QPair<QVariant, QVariantMap> result
        = processReply(method.toString(), request.value("params"));
    if (!reply.contains("id"))
        return QVariantMap();

    if (!result.second.isEmpty()) {
        reply["error"] = result.second;
        return reply;
    }

    reply["result"] = result.first;
    return reply;
}

inline QPair<QVariant, QVariantMap> Node::processReply(const QString &method, const QVariant &args)
{
    if (!priv->methods)
        return qMakePair(QVariant(), QVariantMap({{"code", METHOD_NOT_FOUND}, {"message", "Method not found"}}));

    if (args.type() != QVariant::List && !args.isNull())
        return qMakePair(QVariant(), QVariantMap({{"code", INVALID_PARAMS}, {"message", "Invalid params"}}));

    QVariantList params = args.toList();

    // 10 is the max number of args supported by moc/qobject/...
    if (params.size() > 10)
    return qMakePair(QVariant(), QVariantMap({{"code", INVALID_PARAMS}, {"message", "Invalid params"}}));

    const QMetaObject *metaObject = priv->methods->metaObject();
    int i = indexOfMethod(metaObject, method, params);

    if (i == -1)
        return qMakePair(QVariant(), QVariantMap({{"code", METHOD_NOT_FOUND}, {"message", "Method not found"}}));

    QMetaMethod metaMethod = metaObject->method(i);

    {
        int size = params.size();
        QVector<ArgumentHandler> argsHandler;
        QVector<QGenericArgument> args;

        argsHandler.reserve(size);
        args.reserve(size);

        for (int i = 0;i != size;++i)
            args.push_back(argsHandler[i].convert(params[i]));

        ReturnHandler retHandler;
        QGenericReturnArgument ret = retHandler.convert(metaMethod.typeName());

        metaMethod.invoke(priv->methods, Qt::DirectConnection, ret,
                          (0 < size) ? args[0] : QGenericArgument(),
                          (1 < size) ? args[1] : QGenericArgument(),
                          (2 < size) ? args[2] : QGenericArgument(),
                          (3 < size) ? args[3] : QGenericArgument(),
                          (4 < size) ? args[4] : QGenericArgument(),
                          (5 < size) ? args[5] : QGenericArgument(),
                          (6 < size) ? args[6] : QGenericArgument(),
                          (7 < size) ? args[7] : QGenericArgument(),
                          (8 < size) ? args[8] : QGenericArgument(),
                          (9 < size) ? args[9] : QGenericArgument());

        return qMakePair(QVariant(retHandler), QVariantMap());
    }
}

} // namespace Rpc
} // namespace libbta
