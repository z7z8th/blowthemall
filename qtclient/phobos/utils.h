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
#include <QMetaMethod>
#include <QVector>

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

inline QString methodNameFromSignature(const char *signature)
{
    QString methodName = QString::fromLocal8Bit(signature);
    int i = methodName.indexOf('(');
    return methodName.left(i);
}

inline QVariant convertToMostCommon(QVariant variant)
{
    switch (variant.type()) {
    case QVariant::UInt:
    case QVariant::LongLong:
    case QVariant::ULongLong:
        variant.convert(QVariant::Int);
    default:
        break;
    }
    return variant;
}

inline int indexOfMethod(const QMetaObject *metaObject,
                         const QString &methodName, const QVariantList &params)
{
    for (int i = 0;i < metaObject->methodCount();++i) {
        QMetaMethod m = metaObject->method(i);

        if (methodName != methodNameFromSignature(m.signature()))
            continue;

        QList<QByteArray> parameterTypes = m.parameterTypes();

        if (params.size() != parameterTypes.size())
            continue;

        bool paramsOk = true;
        for (int j = 0;j < params.size();++j) {
            if (convertToMostCommon(params[j]).typeName()
                    != parameterTypes[j]) {
                paramsOk = false;
                break;
            }
        }

        if (paramsOk)
            return i;
    }

    return -1;
}

class ArgumentsHandler
{
public:
    QVector<QGenericArgument> convert(const QVariantList &params)
    {
        QVector<QGenericArgument> args(10);

        for (int i = 0;i < params.size();++i) {
            QVariant variant = convertToMostCommon(params[0]);
            const void *data;

            switch (variant.type()) {
            case QVariant::String:
                stringBuffer[i] = variant.toString();
                data = &stringBuffer[i];
                break;
            case QVariant::Int:
                intBuffer[i] = variant.toInt();
                data = &intBuffer[i];
                break;
            case QVariant::Double:
                doubleBuffer[i] = variant.toDouble();
                data = &doubleBuffer[i];
                break;
            case QVariant::Map:
                mapBuffer[i] = variant.toMap();
                data = &mapBuffer[i];
                break;
            case QVariant::List:
                listBuffer[i] = variant.toList();
                data = &listBuffer[i];
                break;
            case QVariant::Bool:
                boolBuffer[i] = variant.toBool();
                data = &boolBuffer[i];
                break;
            default:
                // This should never happen, because all possible JSON values
                // have been mapped in the previous code
                continue;
            }

            args[i] = QGenericArgument(variant.typeName(), data);
        }

        return args;
    }

private:
    QMap<int, QString> stringBuffer;
    QMap<int, int> intBuffer;
    QMap<int, double> doubleBuffer;
    QMap<int, QVariantMap> mapBuffer;
    QMap<int, QVariantList> listBuffer;
    QMap<int, bool> boolBuffer;
};

class ReturnHandler
{
public:
    QGenericReturnArgument convert(const QByteArray &typeName)
    {
        QGenericReturnArgument ret;

        if (typeName == "QString") {
            ret = Q_RETURN_ARG(QString, stringBuffer);
            used = QVariant::String;
        } else if (typeName == "int") {
            ret = Q_RETURN_ARG(int, intBuffer);
            used = QVariant::Int;
        } else if (typeName == "double") {
            ret = Q_RETURN_ARG(double, doubleBuffer);
            used = QVariant::Double;
        } else if (typeName == "QVariantMap") {
            ret = Q_RETURN_ARG(QVariantMap, mapBuffer);
            used = QVariant::Map;
        } else if (typeName == "QVariantList") {
            ret = Q_RETURN_ARG(QVariantList, listBuffer);
            used = QVariant::List;
        } else if (typeName == "bool") {
            ret = Q_RETURN_ARG(bool, boolBuffer);
            used = QVariant::Bool;
        }

        return ret;
    }

    operator QVariant ()
    {
        switch (used) {
        case QVariant::String:
            return stringBuffer;
        case QVariant::Int:
            return intBuffer;
        case QVariant::Double:
            return doubleBuffer;
        case QVariant::Map:
            return mapBuffer;
        case QVariant::List:
            return listBuffer;
        case QVariant::Bool:
            return boolBuffer;
        default:
            return QVariant();
        }
    }

private:
    QString stringBuffer;
    int intBuffer;
    double doubleBuffer;
    QVariantMap mapBuffer;
    QVariantList listBuffer;
    bool boolBuffer;

    QVariant::Type used;
};

} // namespace Phobos

#endif // PHOBOSUTILS_H
