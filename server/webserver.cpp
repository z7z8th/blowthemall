#include "webserver.h"
#include "handler.h"

#include <Tufao/WebSocket>

#include "phobos-tufao/jsonrpc.h"

WebServer::WebServer(QObject *parent) :
    Tufao::HttpServer(parent)
{
}

void WebServer::upgrade(Tufao::HttpServerRequest *request,
                        const QByteArray &head)
{
    Tufao::WebSocket *socket = new Tufao::WebSocket(this);
    Handler *handler = new Handler(socket);
    new JsonRpc(handler, socket, socket);

    connect(socket, SIGNAL(disconnected()), socket, SLOT(deleteLater()));

    socket->startServerHandshake(request, head);
}
