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

#include "procedure.h"
#include "utils.h"
#include <QUuid>

using namespace Phobos;

Procedure::Procedure(const QString &method, QObject *parent) :
    QObject(parent),
    m_method(method)
{
}

bool Procedure::connectToObject(QObject *object)
{
    bool ok;

    ok = connect(this, SIGNAL(readyCall(QString,QVariant,QVariant)),
                 object, SLOT(call(QString,QVariant,QVariant)));

    if (!ok)
        return false;

    ok = connect(object, SIGNAL(readyResponse(QVariant,QVariant)),
                 this, SLOT(onReadyResponse(QVariant,QVariant)));

    if (!ok)
        disconnect(this, SIGNAL(readyCall(QString,QVariant,QVariant)),
                   object, SLOT(call(QString,QVariant,QVariant)));

    return ok;
}

void Phobos::Procedure::disconnectFromObject(QObject *object)
{
    disconnect(this, SIGNAL(readyCall(QString,QVariant,QVariant)),
               object, SLOT(call(QString,QVariant,QVariant)));
    disconnect(object, SIGNAL(readyResponse(QVariant,QVariant)),
               this, SLOT(onReadyResponse(QVariant,QVariant)));
}

Procedure & Procedure::operator ()(const QVariant &arg0, const QVariant &arg1,
                                   const QVariant &arg2, const QVariant &arg3,
                                   const QVariant &arg4, const QVariant &arg5,
                                   const QVariant &arg6, const QVariant &arg7,
                                   const QVariant &arg8, const QVariant &arg9)
{
    call(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
    return *this;
}

void Procedure::call(const QVariant &arg0, const QVariant &arg1,
                     const QVariant &arg2, const QVariant &arg3,
                     const QVariant &arg4, const QVariant &arg5,
                     const QVariant &arg6, const QVariant &arg7,
                     const QVariant &arg8, const QVariant &arg9)
{
    QString id = QUuid::createUuid();
    emit readyCall(m_method,
                   createParams(arg0, arg1, arg2, arg3, arg4,
                                arg5, arg6, arg7, arg8, arg9),
                   id);
    usedIds.insert(id);
}

void Procedure::onReadyResponse(const QVariant &result, const QVariant &id)
{
    if (usedIds.contains(id.toString())) {
        emit this->result(result);
        usedIds.remove(id.toString());
    }
}
