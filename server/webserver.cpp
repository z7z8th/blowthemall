#include "webserver.h"

#include <Tufao/WebSocket>
#include <Tufao/HttpServerRequest>
#include <Tufao/Url>

#include "phobos-tufao/jsonrpc.h"

WebServer::WebServer(QObject *parent) :
    Tufao::HttpServer(parent)
{
}

void WebServer::upgrade(Tufao::HttpServerRequest *request,
                        const QByteArray &)
{
    Tufao::HttpServerResponse response(request->socket(),
                                       request->responseOptions());
    response.writeHead(Tufao::HttpServerResponse::NOT_FOUND);
    response.end("Not found\n");
}
