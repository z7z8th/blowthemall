#ifndef BASESTATE_H
#define BASESTATE_H

#include <QObject>

class BaseState : public QObject
{
    Q_OBJECT
public:
    explicit BaseState(QObject *parent = 0);

public slots:
    Q_INVOKABLE QString protocol_version();
//    void match_log(QHash<QString, QString> object);
//    void change_state(const QString &new_state);
//    void player_out(const QString &id);
};

#endif // BASESTATE_H
