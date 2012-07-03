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

#ifndef LIBBTA_PRIV_RPCNODE_H
#define LIBBTA_PRIV_RPCNODE_H

#include "../rpcnode.h"
#include <qjson/serializer.h>

inline uint qHash(const QVariant &variant)
{
    return variant.toUInt();
}

template<class T>
QVariantMap jsonRpcObject(const QString &remoteMethod, const T &args)
{
    QVariantMap object;

    object["jsonrpc"] = "2.0";
    object["method"] = remoteMethod;

    if (!args.isEmpty())
        object["params"] = args;

    return object;
}

namespace libbta {
namespace Rpc {

struct Node::Priv
{
    Priv() : methods(NULL), socket(NULL), index(0) {}

    template<class T>
    QVariant callWith(const QString &remoteMethod, const T &args,
                      std::function<void (QVariant)> receiver)
    {
        if (!socket)
            return QVariant();

        QVariant id = index++;
        QVariantMap object = jsonRpcObject(remoteMethod, args);
        object["id"] = id;

        if (!socket->sendMessage(QJson::Serializer().serialize(object)))
            return QVariant();

        calls[id] = receiver;
        return id;
    }

    template<class T>
    void call(const QString &remoteMethod, const T &args)
    {
        if (!socket)
            return;

        socket->sendMessage(QJson::Serializer()
                            .serialize(jsonRpcObject(remoteMethod, args)));
    }

    QObject *methods;
    Tufao::AbstractMessageSocket *socket;
    uint index;

    QHash<QVariant, std::function<void (QVariant)>> calls;
};

} // namespace Rpc
} // namespace libbta

#endif // LIBBTA_PRIV_RPCNODE_H
