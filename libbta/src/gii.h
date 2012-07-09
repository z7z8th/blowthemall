#ifndef LIBBTA_GII_GII_H
#define LIBBTA_GII_GII_H

#include <QObject>

namespace libbta {
namespace Gii {

class Gii : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString defaultState
               READ defaultState
               WRITE setDefaultState
               NOTIFY defaultStateChanged)
    Q_PROPERTY(QObjectList states
               READ states
               WRITE setStates
               NOTIFY statesChanged)
public:
    explicit Gii(QObject *parent = 0);

    QString defaultState();
    void setDefaultState(const QString &state);

    QObjectList states();
    void setStates(const QObjectList &state);

signals:
    void defaultStateChanged();
    void statesChanged();
    
public slots:
    void save(const QString &file);
    void load(const QString &file);
};

} // namespace Gii
} // namespace libbta

#endif // LIBBTA_GII_GII_H
