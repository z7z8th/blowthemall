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

#ifndef RESPONSEHANDLER_H
#define RESPONSEHANDLER_H

#include "phobosrpc_global.h"
#include <QVariant>
#include <QPointer>

namespace Phobos {

class Peer;

enum class ErrorCode
{
    NO_ERROR,
    PARSE_ERROR      = -32700,
    INVALID_REQUEST  = -32600,
    METHOD_NOT_FOUND = -32601,
    INVALID_PARAMS   = -32602,
    INTERNAL_ERROR   = -32603
};

struct PHOBOSRPC_EXPORT Error
{
    Error(ErrorCode code, QString desc);
    Error(ErrorCode code = ErrorCode::NO_ERROR);
    Error(const Error &) = default;

    // generates the JSON object
    operator QByteArray() const;
    // generates the QVariant object, which can be parsed into a JSON Object
    operator QVariantMap() const;

    ErrorCode code;
    QString desc;
};

class PHOBOSRPC_EXPORT ResponseHandler
{
public:
    explicit ResponseHandler(Peer *peer = 0);

    QString method() const;
    bool setMethod(const QString &method);

    bool hasParams() const;
    QVariant params() const;
    bool setParams(const QVariant &params);
    void resetParams();

    /*!
      @return true if the response has an id
      */
    bool hasId() const;
    /*!
      @return the id, or a null QVariant if id doesn't exist
      */
    QVariant id() const;
    /*! validates and sets the id
      this id will be used in the JSON-RPC response message object
      @return returns true if \param id is a valid id
      @sa hasId
      */
    bool setId(const QVariant &id);
    /*! removes any id associated with the response object
      @sa setId
      */
    void resetId();

    /*!
      @return false if you can send a reply to the peer object
      */
    bool isNull() const;
    /*! sends the response object to the peer object, if it still exists
      * use this method when you wants send the response.
      * use this method will put the object in the null state.
      * use this method when the object is in null state won't do anything
      */
    void response(const QVariant &result);
    /*! sends the response error object to the peer object, if it still exists
      * use this method when you wants send an error response.
      * use this method will put the object in the null state.
      * use this method when the object is in null state won't do anything
      */
    void error(const Error &error);

private:
    QPointer<Peer> peer;

    QString m_method;

    QVariant m_params;

    bool m_hasId;
    QVariant m_id;
};

} // namespace Phobos

#endif // RESPONSEHANDLER_H
