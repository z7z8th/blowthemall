#include "webserver.h"
#include "handler.h"

#include <Tufao/WebSocket>
#include <Tufao/HttpServerRequest>
#include <Tufao/Url>

#include "phobos-tufao/jsonrpc.h"

WebServer::WebServer(QObject *parent) :
    Tufao::HttpServer(parent)
{
}

void WebServer::upgrade(Tufao::HttpServerRequest *request,
                        const QByteArray &head)
{
    if (Tufao::Url(request->url()).path() != "/tracker") {
        Tufao::HttpServerResponse response(request->socket(),
                                           request->responseOptions());
        response.writeHead(Tufao::HttpServerResponse::NOT_FOUND);
        response.end("Not found\n");
        return;
    }

    Tufao::WebSocket *socket = new Tufao::WebSocket(this);
    Handler *handler = new Handler(socket);
    new JsonRpc(handler, socket, socket);

    connect(socket, SIGNAL(disconnected()), socket, SLOT(deleteLater()));

    socket->startServerHandshake(request, head);
}
