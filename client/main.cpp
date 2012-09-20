#include <QtCore/QCoreApplication>
#include <QtNetwork/QHostAddress>
#include <Tufao/WebSocket>
#include "work.h"

using namespace Tufao;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    WebSocket ws;
    ws.connectToHost(QHostAddress::LocalHost, 8080, "/");

    Work work(&ws);

    QObject::connect(&ws, SIGNAL(connected()), &work, SLOT(doWork()));

    return a.exec();
}
