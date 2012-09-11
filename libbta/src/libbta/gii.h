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

#ifndef LIBBTA_GII_GII_H
#define LIBBTA_GII_GII_H

#include "giistate.h"
#include <QtCore/QHash>

namespace libbta {
namespace Gii {

typedef QHash<QString, State*> States;

class LIBBTA_EXPORT Gii : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString defaultState
               READ defaultState
               WRITE setDefaultState
               NOTIFY defaultStateChanged)
    Q_PROPERTY(States states
               READ states
               WRITE setStates
               NOTIFY statesChanged)

    Q_PROPERTY(State* currentState
               READ currentState
               NOTIFY currentStateChanged)
    Q_PROPERTY(QString currentStateString
               READ currentStateString
               NOTIFY currentStateChanged)
public:
    explicit Gii(QObject *parent = 0);
    ~Gii();

    QString defaultState();
    void setDefaultState(const QString &state);

    States states();
    void setStates(const States &states);

    State *currentState();
    QString currentStateString();

    Q_INVOKABLE bool save(const QString &file);
    Q_INVOKABLE bool load(const QString &file);

signals:
    void defaultStateChanged();
    void statesChanged();

    void currentStateChanged();
    
public slots:
    void loadState(const QString &state);
    void clear();

private slots:
    void onStateFinished();

private:
    struct Priv;
    Priv *priv;
};

} // namespace Gii
} // namespace libbta

#endif // LIBBTA_GII_GII_H
