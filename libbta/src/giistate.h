/*
  Copyright © 2012  Vinícius dos Santos Oliveira

  This file is part of libbta.

  libbta is free software: you can redistribute it and/or modify
  it under the terms of the GNU Lesser General Public License as published
  by the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
  */

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
    ~State();

    int period();
    void setPeriod(int period);

    QStringList seq();
    void setSeq(const QStringList &seq);

    QString onFinished();
    void setOnFinished(const QString &onFinished);

    QString currentFrame();

signals:
    void periodChanged();
    void seqChanged();
    void onFinishedChanged();

    void currentFrameChanged();
    void finished();

public slots:
    void start();
    void stop();

private slots:
    void onTimeout();

private:
    struct Priv;
    Priv *priv;
};

} // namespace Gii
} // namespace libbta

#endif // LIBBTA_GII_GIISTATE_H
