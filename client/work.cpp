#include "work.h"
#include <libbta/RpcNode>

#include <QtDebug>

using namespace Tufao;
using namespace libbta::Rpc;

Work::Work(WebSocket *ws, QObject *parent) :
    QObject(parent),
    node(ws)
{
    connect(&node, SIGNAL(error(QVariant,QByteArray)),
            this, SLOT(onError(QVariant,QByteArray)));
}

void Work::doWork()
{
    qDebug("connected");
//    node.setMethods();

    node.callWith("protocol_version", QVariantList(), [](const QVariant &result){
          qDebug() << result;
    });
}

void Work::onError(QVariant data, QByteArray msg)
{
    qDebug() << data << msg;
}
