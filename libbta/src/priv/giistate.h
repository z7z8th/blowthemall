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

#ifndef LIBBTA_PRIV_GIISTATE_H
#define LIBBTA_PRIV_GIISTATE_H

#include "../giistate.h"
#include <QtCore/QTimer>

namespace libbta {
namespace Gii {

struct State::Priv
{
    Priv() {
        timer.setSingleShot(true);
    }

    int period = 0;
    QStringList seq;
    QString onFinished;

    int currentFrame = -1;

    QTimer timer;
};

} // namespace Rpc
} // namespace libbta

#endif // LIBBTA_PRIV_GIISTATE_H
