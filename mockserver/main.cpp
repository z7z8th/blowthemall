#include <QtCore/QCoreApplication>
#include "httpserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    HttpServer server;
    server.listen(QHostAddress::Any, 8080);

    return a.exec();
}
