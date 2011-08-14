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

#ifndef PROCEDURE_H
#define PROCEDURE_H

#include "phobosrpc_global.h"
#include <QObject>
#include <QVariant>
#include <QSet>

namespace Phobos {

class PHOBOSRPC_EXPORT Procedure : public QObject
{
    Q_OBJECT
public:
    explicit Procedure(const QString &method, QObject *parent = 0);

    bool connectToObject(QObject *object);
    void disconnectFromObject(QObject *object);

signals:
    void readyCall(QString method, QVariant params, QVariant id);

    void result(QVariant);

public:
    Procedure & operator ()(const QVariant &arg0 = QVariant(),
                            const QVariant &arg1 = QVariant(),
                            const QVariant &arg2 = QVariant(),
                            const QVariant &arg3 = QVariant(),
                            const QVariant &arg4 = QVariant(),
                            const QVariant &arg5 = QVariant(),
                            const QVariant &arg6 = QVariant(),
                            const QVariant &arg7 = QVariant(),
                            const QVariant &arg8 = QVariant(),
                            const QVariant &arg9 = QVariant());

public slots:
    void call(const QVariant &arg0 = QVariant(),
              const QVariant &arg1 = QVariant(),
              const QVariant &arg2 = QVariant(),
              const QVariant &arg3 = QVariant(),
              const QVariant &arg4 = QVariant(),
              const QVariant &arg5 = QVariant(),
              const QVariant &arg6 = QVariant(),
              const QVariant &arg7 = QVariant(),
              const QVariant &arg8 = QVariant(),
              const QVariant &arg9 = QVariant());

    void onReadyResponse(const QVariant &result, const QVariant &id);

private:
    QString m_method;
    QSet<QString> usedIds;
};

} // namespace Phobos

#endif // PROCEDURE_H
