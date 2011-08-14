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

#ifndef PHOBOSSERVER_H
#define PHOBOSSERVER_H

#include "phobosrpc_global.h"
#include <QObject>
#include <QSharedPointer>

namespace Phobos {

class ResponseHandler;

class PHOBOSRPC_EXPORT Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = 0);

public:
    void setObject(QObject *object);

    bool connectToObject(QObject *object);
    void disconnectFromObject(QObject *object);

public slots:
    void request(QSharedPointer<Phobos::ResponseHandler> handler);

private:
    QObject *m_object;
};

} // namespace Phobos

#endif // PHOBOSSERVER_H
