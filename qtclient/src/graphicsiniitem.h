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

#ifndef GRAPHICSINIITEM_H
#define GRAPHICSINIITEM_H

#include <QSettings>
#include <QGraphicsSvgItem>
#include <QSharedPointer>
#include <QTimer>

class QSvgRenderer;

class GraphicsIniItem : public QGraphicsSvgItem
{
    Q_OBJECT
public:
    explicit GraphicsIniItem(const QString &prefix, QGraphicsItem *parent = 0);

signals:
    void stateChanged(QString);
    void finished();

public slots:
    bool loadState(const QString &state);

private slots:
    void nextFrame();

private:
    struct State
    {
        int period;
        QList<QString> frames;
        QString onFinished;
    };

    bool loadFrame(int frame);

    QString prefix;
    QSettings settings;
    State currentState;
    int currentFrame;
    QSvgRenderer *currentRenderer;
    QTimer timer;
};

#endif // GRAPHICSINIITEM_H
