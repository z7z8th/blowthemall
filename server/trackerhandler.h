#ifndef HANDLER_H
#define HANDLER_H

#include <QObject>

class Tracker;

class TrackerHandler : public QObject
{
    Q_OBJECT
public:
    explicit TrackerHandler(QObject *parent = 0);

    Q_INVOKABLE int publishTimeout();

private:
    Tracker &tracker;
};

#endif // HANDLER_H
