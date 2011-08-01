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

#include "loginscreen.h"
#include "ui_loginscreen.h"
#include <QDesktopServices>
#include <QUrl>

LoginScreen::LoginScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginScreen)
{
    ui->setupUi(this);
}

LoginScreen::~LoginScreen()
{
    delete ui;
}

void LoginScreen::on_internetRadioButton_toggled(bool checked)
{
    if (checked) {
        ui->anonymousCheckBox->setEnabled(true);
        on_anonymousCheckBox_toggled(ui->anonymousCheckBox->isChecked());
    } else {
        ui->anonymousCheckBox->setEnabled(false);
        on_anonymousCheckBox_toggled(true); // play anonymously
    }
}

void LoginScreen::on_anonymousCheckBox_toggled(bool checked)
{
    if (checked) {
        ui->passwdLineEdit->setEnabled(false);
        ui->storePasswdCheckBox->setEnabled(false);
    } else {
        ui->passwdLineEdit->setEnabled(true);
        ui->storePasswdCheckBox->setEnabled(true);
    }
}

void LoginScreen::on_registerButton_clicked()
{
    QDesktopServices::openUrl(QUrl("http://blowthemall.googlecode.com/"));
}
