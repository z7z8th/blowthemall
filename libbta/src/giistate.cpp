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

#include "priv/giistate.h"

namespace libbta {
namespace Gii {

State::State(QObject *parent) :
    QObject(parent),
    priv(new Priv)
{
    connect(&priv->timer, SIGNAL(timeout()), this, SLOT(onTimeout()));
}

State::~State()
{
    delete priv;
}

int State::period()
{
    return priv->period;
}

void State::setPeriod(int period)
{
    if (period == priv->period)
        return;

    if (period)
        priv->timer.setInterval(period);
    else
        priv->timer.stop();

    priv->period = period;
    emit periodChanged();
}

QStringList State::seq()
{
    return priv->seq;
}

void State::setSeq(const QStringList &seq)
{
    if (seq == priv->seq)
        return;

    priv->currentFrame = seq.size() ? 0 : -1;
    priv->seq = seq;
    emit seqChanged();
}

QString State::onFinished()
{
    return priv->onFinished;
}

void State::setOnFinished(const QString &onFinished)
{
    if (onFinished == priv->onFinished)
        return;

    priv->onFinished = onFinished;
    emit onFinishedChanged();
}

QString State::currentFrame()
{
    if (priv->currentFrame == -1)
        return QString();

    return priv->seq[priv->currentFrame];
}

void State::start()
{
    if (priv->seq.isEmpty())
        return;

    if (priv->period)
        priv->timer.start();

    if (priv->currentFrame) {
        priv->currentFrame = 0;
        emit currentFrameChanged();
    }
}

void State::stop()
{
    priv->timer.stop();
}

void State::onTimeout()
{
    if (priv->currentFrame + 1 == priv->seq.size()) {
        emit finished();
        return;
    }

    priv->currentFrame += 1;
    priv->timer.start();
    emit currentFrameChanged();
}

} // namespace Gii
} // namespace libbta
