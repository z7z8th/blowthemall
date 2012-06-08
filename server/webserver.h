#ifndef WEBSERVER_H
#define WEBSERVER_H

#include <Tufao/HttpServer>

class WebServer : public Tufao::HttpServer
{
    Q_OBJECT
public:
    explicit WebServer(QObject *parent = 0);
    
protected:
    void upgrade(Tufao::HttpServerRequest *request, const QByteArray &head);
};

#endif // WEBSERVER_H
