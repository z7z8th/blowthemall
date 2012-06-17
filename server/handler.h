#ifndef HANDLER_H
#define HANDLER_H

#include <QObject>

class Tracker;

class Handler : public QObject
{
    Q_OBJECT
public:
    explicit Handler(QObject *parent = 0);

    Q_INVOKABLE int publishTimeout();

private:
    Tracker &tracker;
};

#endif // HANDLER_H
