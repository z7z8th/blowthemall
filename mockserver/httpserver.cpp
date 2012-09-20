#include "httpserver.h"
#include "basestate.h"

#include <Tufao/WebSocket>
#include <libbta/RpcNode>

using namespace Tufao;
using namespace libbta::Rpc;

::HttpServer::HttpServer(QObject *parent) :
    Tufao::HttpServer(parent)
{
}

void ::HttpServer::upgrade(HttpServerRequest *request, const QByteArray &head)
{
    qDebug("upgrade");
    WebSocket *ws = new WebSocket(this);
    Node *node = new Node(ws, this);
    BaseState *state = new BaseState(this);

    connect(ws, SIGNAL(disconnected()), ws, SLOT(deleteLater()));
    connect(ws, SIGNAL(disconnected()), node, SLOT(deleteLater()));
    connect(ws, SIGNAL(disconnected()), state, SLOT(deleteLater()));

    node->setMethods(state);

    ws->startServerHandshake(request, head);
}
