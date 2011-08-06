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

#include "trackerscreen.h"
#include "ui_trackerscreen.h"

TrackerScreen::TrackerScreen(const QString &username, const QString &passwd,
                             QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TrackerScreen),
    username(username),
    passwd(passwd)
{
    ui->setupUi(this);
}

TrackerScreen::~TrackerScreen()
{
    delete ui;
}

void TrackerScreen::on_backButton_clicked()
{
    emit backRequest();
}
