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
