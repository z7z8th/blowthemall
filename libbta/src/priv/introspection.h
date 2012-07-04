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

#ifndef INTROSPECTION_H
#define INTROSPECTION_H

#include <QtCore/QMetaMethod>

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
                         const QString &methodName,
                         const QVariantList &params,
                         bool lookForAllTypes = false)
{
    for (int i = 0;i < metaObject->methodCount();++i) {
        QMetaMethod m = metaObject->method(i);

        if (!lookForAllTypes
                && m.methodType() != QMetaMethod::Method)
            continue;

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

class ArgumentHandler
{
public:
    QGenericArgument convert(const QVariant &param)
    {
        QVariant variant = convertToMostCommon(param);
        const void *data;

        switch (variant.type()) {
        case QVariant::String:
            stringBuffer = variant.toString();
            data = &stringBuffer;
            break;
        case QVariant::Int:
            intBuffer = variant.toInt();
            data = &intBuffer;
            break;
        case QVariant::Double:
            doubleBuffer = variant.toDouble();
            data = &doubleBuffer;
            break;
        case QVariant::Map:
            mapBuffer = variant.toMap();
            data = &mapBuffer;
            break;
        case QVariant::List:
            listBuffer = variant.toList();
            data = &listBuffer;
            break;
        case QVariant::Bool:
            boolBuffer = variant.toBool();
            data = &boolBuffer;
            break;
        default:
            // This should never happen, because all possible JSON values
            // have been mapped in the previous code
            return QGenericArgument();
        }

        return QGenericArgument(variant.typeName(), data);
    }

private:
    QString stringBuffer;
    int intBuffer;
    double doubleBuffer;
    QVariantMap mapBuffer;
    QVariantList listBuffer;
    bool boolBuffer;
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

#endif // INTROSPECTION_H
