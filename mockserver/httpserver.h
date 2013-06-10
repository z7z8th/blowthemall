#ifndef HTTPSERVER_H
#define HTTPSERVER_H

#include <Tufao/HttpServer>

class HttpServer : public Tufao::HttpServer
{
    Q_OBJECT
public:
    explicit HttpServer(QObject *parent = 0);

protected:
    void upgrade(Tufao::HttpServerRequest *request, const QByteArray &head);
};

#endif // HTTPSERVER_H
