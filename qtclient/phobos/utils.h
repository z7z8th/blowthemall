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

#ifndef PHOBOSUTILS_H
#define PHOBOSUTILS_H

#include <QVariant>

namespace Phobos {

inline bool isRequestMessage(const QVariantMap &object)
{
    if (object.contains("method"))
        return true;
    else
        return false;
}

inline bool isRequestMessage(const QVariantList &objectList)
{
    if (objectList.size())
        return true;
    else
        return false;
}

inline bool isRequestMessage(const QVariant &object)
{
    switch (object.type()) {
    case QVariant::Map:
        return isRequestMessage(object.toMap());
    case QVariant::List:
        return isRequestMessage(object.toList());
    default:
        return false;
    }
}

inline bool isResponseMessage(const QVariantMap &object)
{
    if (object.contains("result")
            || object.contains("error"))
        return true;
    else
        return false;
}

inline bool isResponseMessage(const QVariantList &objectList)
{
    if (objectList.size())
        return true;
    else
        return false;
}

inline bool isResponseMessage(const QVariant &object)
{
    switch (object.type()) {
    case QVariant::Map:
        return isResponseMessage(object.toMap());
    case QVariant::List:
        return isResponseMessage(object.toList());
    default:
        return false;
    }
}

inline QVariantList createParams(const QVariant &arg0, const QVariant &arg1,
                                 const QVariant &arg2, const QVariant &arg3,
                                 const QVariant &arg4, const QVariant &arg5,
                                 const QVariant &arg6, const QVariant &arg7,
                                 const QVariant &arg8, const QVariant &arg9)
{
    QVariantList params;

    if (arg0.isNull())
        goto READY_PARAMS;

    params.append(arg0);

    if (arg1.isNull())
        goto READY_PARAMS;

    params.append(arg1);

    if (arg2.isNull())
        goto READY_PARAMS;

    params.append(arg2);

    if (arg3.isNull())
        goto READY_PARAMS;

    params.append(arg3);

    if (arg4.isNull())
        goto READY_PARAMS;

    params.append(arg4);

    if (arg5.isNull())
        goto READY_PARAMS;

    params.append(arg5);

    if (arg6.isNull())
        goto READY_PARAMS;

    params.append(arg6);

    if (arg7.isNull())
        goto READY_PARAMS;

    params.append(arg7);

    if (arg8.isNull())
        goto READY_PARAMS;

    params.append(arg8);

    if (arg9.isNull())
        goto READY_PARAMS;

    params.append(arg9);

    READY_PARAMS:
    return params;
}

} // namespace Phobos

#endif // PHOBOSUTILS_H
