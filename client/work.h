#ifndef WORK_H
#define WORK_H

#include <QObject>
#include <Tufao/WebSocket>
#include <libbta/RpcNode>

class Work : public QObject
{
    Q_OBJECT
public:
    explicit Work(Tufao::WebSocket *ws, QObject *parent = 0);

public slots:
    void doWork();
    void onError(QVariant,QByteArray);

private:
    libbta::Rpc::Node node;
};

#endif // WORK_H
