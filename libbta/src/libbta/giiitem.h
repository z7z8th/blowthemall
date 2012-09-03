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

#ifndef LIBBTA_GIIITEM_H
#define LIBBTA_GIIITEM_H

#include <QtDeclarative/QDeclarativeItem>

namespace libbta {
namespace Gii {

class State;

class Item : public QDeclarativeItem
{
    Q_OBJECT
    Q_DISABLE_COPY(Item)
    Q_PROPERTY(QString file
               READ file
               WRITE setFile
               NOTIFY fileChanged)
public:
    explicit Item(QDeclarativeItem *parent = 0);
    ~Item();

    QString file();
    void setFile(const QString &file);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *);

    /*!
     * It will register the GiiItem in the uri "org.blowthemall.gii", under the
     * "GiiItem" qml name.
     */
    static int registerType();

signals:
    void fileChanged();

public slots:
    void loadState(const QString &state);

private slots:
    void onFrameChanged();
    void onStateChanged();

private:
    void updateState(State *state);

    struct Priv;
    Priv *priv;
};

} // namespace Gii
} // namespace libbta

QML_DECLARE_TYPE(libbta::Gii::Item)

#endif // LIBBTA_GIIITEM_H
