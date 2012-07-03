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

namespace libbta {
namespace Rpc {

Node::Node(QObject *parent) :
    QObject(parent),
    priv(new Priv)
{
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

Tufao::AbstractMessageSocket Node::messageSocket()
{
    return priv->socket;
}

void Node::setMessageSocket(Tufao::AbstractMessageSocket *socket)
{
    priv->socket = socket;
}

QVariant Node::callWith(const QString &remoteMethod, const QVariantList &args,
                        std::function<void (QVariant)> receiver)
{
}

QVariant Node::callWith(const QString &remoteMethod, const QVariantMap &args,
                        std::function<void (QVariant)> receiver)
{
}

void Node::call(const QString &remoteMethod, const QVariantList &args)
{
}

void Node::call(const QString &remoteMethod, const QVariantMap &args)
{
}

} // namespace Rpc
} // namespace libbta
