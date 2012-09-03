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

#include "priv/giiitem.h"
#include <QtDeclarative/QtDeclarative>
#include <QtSvg/QSvgRenderer>

namespace libbta {
namespace Gii {

Item::Item(QDeclarativeItem *parent) :
    QDeclarativeItem(parent),
    priv(new Priv)
{
    setFlag(QGraphicsItem::ItemHasNoContents, false);

    connect(&priv->gii, SIGNAL(currentStateChanged()),
            this, SLOT(onStateChanged()));
}

Item::~Item()
{
    delete priv;
}

QString Item::file()
{
    return priv->file;
}

void Item::setFile(const QString &file)
{
    if (file == priv->file)
        return;

    priv->gii.load(file);
    priv->file = file;

    updateState(priv->gii.currentState());
    emit fileChanged();
}

void Item::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                 QWidget *)
{
    if (!priv->currentState)
        return;

    painter->save();
    QSvgRenderer(priv->currentState->currentFrame())
            .render(painter, option->rect);
    painter->restore();
}

int Item::registerType()
{
    return qmlRegisterType<Item>("org.blowthemall.gii", 1, 0, "GiiItem");
}

inline void Item::updateState(State *state)
{
    if (priv->currentState) {
        disconnect(priv->currentState, SIGNAL(currentFrameChanged()),
                   this, SLOT(onFrameChanged()));
    }

    priv->currentState = priv->gii.currentState();

    if (state)
        connect(state, SIGNAL(currentFrameChanged()),
                this, SLOT(onFrameChanged()));

//    update();
    QGraphicsScene *scene = QGraphicsItem::scene();
    if (scene)
        scene->update();
}

void Item::onFrameChanged()
{
//    update();
    QGraphicsScene *scene = QGraphicsItem::scene();
    if (scene)
        scene->update();
}

void Item::onStateChanged()
{
    updateState(priv->gii.currentState());
}

void Item::loadState(const QString &state)
{
    priv->gii.loadState(state);
}

} // namespace Gii
} // namespace libbta
