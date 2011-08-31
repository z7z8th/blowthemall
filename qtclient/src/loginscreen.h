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

#ifndef LOGINSCREEN_H
#define LOGINSCREEN_H

#include <QWidget>

namespace Ui {
    class LoginScreen;
}

class LoginScreen : public QWidget
{
    Q_OBJECT

public:
    explicit LoginScreen(QWidget *parent = 0);
    ~LoginScreen();

signals:
    void backRequest();
    void playRequest();

public:
    bool isLanGame();
    QString username();
    QString password();

private slots:
    void on_backButton_clicked();

    void on_internetRadioButton_toggled(bool checked);

    void on_anonymousCheckBox_toggled(bool checked);

    void on_registerButton_clicked();

    void on_playButton_clicked();

private:
    void writeSettings();
    void readSettings();

    Ui::LoginScreen *ui;
};

#endif // LOGINSCREEN_H
