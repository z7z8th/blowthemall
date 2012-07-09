#ifndef LIBBTA_GII_GIISTATE_H
#define LIBBTA_GII_GIISTATE_H

#include <QtCore/QObject>
#include <QtCore/QStringList>

namespace libbta {
namespace Gii {

class State : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int period
               READ period
               WRITE setPeriod
               NOTIFY periodChanged)
    Q_PROPERTY(QStringList seq
               READ seq
               WRITE setSeq
               NOTIFY seqChanged)
    Q_PROPERTY(QString onFinished
               READ onFinished
               WRITE setOnFinished
               NOTIFY onFinishedChanged)
public:
    explicit State(QObject *parent = 0);

    int period();
    void setPeriod(int period);

    QStringList seq();
    void setSeq(const QStringList &seq);

    QString onFinished();
    void setOnFinished(const QString &onFinished);

signals:
    void periodChanged();
    void seqChanged();
    void onFinishedChanged();
};

} // namespace Gii
} // namespace libbta

#endif // LIBBTA_GII_GIISTATE_H
