#include "webserver.h"
#include "trackerhandler.h"

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
    TrackerHandler *handler = new TrackerHandler(socket);
    new JsonRpc(handler, socket, socket);

    connect(socket, SIGNAL(disconnected()), socket, SLOT(deleteLater()));

    socket->startServerHandshake(request, head);
}
