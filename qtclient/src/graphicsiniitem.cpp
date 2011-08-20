/*
  Copyright © 2011  Vinícius dos Santos Oliveira

  This file is part of BlowThemAll.

  BlowThemAll is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published
  by the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
  */

#include "graphicsiniitem.h"
#include <QSvgRenderer>

GraphicsIniItem::GraphicsIniItem(const QString &prefix, QGraphicsItem *parent) :
    QGraphicsSvgItem(parent),
    prefix(prefix),
    settings(prefix + "index.ini", QSettings::IniFormat),
    currentFrame(0),
    currentRenderer(NULL)
{
    timer.setSingleShot(true);
    connect(&timer, SIGNAL(timeout()), this, SLOT(nextFrame()));

    if (!settings.contains("defaultState"))
        return;

    QString defaultState = settings.value("defaultState").toString();

    loadState(defaultState);
}

bool GraphicsIniItem::loadState(const QString &state)
{
    QString stateSectionPrefix = "state." + state + '/';
    State newState;

    {
        QString key = stateSectionPrefix + "period";
        if (!settings.contains(key)
                || !settings.value(key).canConvert(QVariant::Int))
            return false;

        newState.period = settings.value(key).toInt();
    }

    {
        QString key = stateSectionPrefix + "seq";
        if (!settings.contains(key)
                || !settings.value(key).canConvert(QVariant::StringList))
            return false;

        newState.frames = settings.value(key).toStringList();

        if (newState.frames.size() == 0)
            return false;
    }

    {
        QString key = stateSectionPrefix + "onFinished";
        if (settings.contains(key))
            newState.onFinished = settings.value(key).toString();
    }

    currentState = newState;

    return loadFrame(0);
}

void GraphicsIniItem::nextFrame()
{
    if (!loadFrame(currentFrame + 1))
        loadState(currentState.onFinished);
}

bool GraphicsIniItem::loadFrame(int frame)
{
    if (frame >= currentState.frames.size())
        return false;

    // stores current frame
    currentFrame = frame;

    // updates the image to be rendered
    if (currentRenderer)
        delete currentRenderer;

    currentRenderer = new QSvgRenderer(prefix
                                       + currentState.frames[currentFrame],
                                       this);

    setSharedRenderer(currentRenderer);

    // starts the timer
    if (currentState.period)
        timer.start(currentState.period);

    return true;
}
