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
#include <QSettings>
#include <QMessageBox>

LoginScreen::LoginScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginScreen)
{
    ui->setupUi(this);
    readSettings();
}

LoginScreen::~LoginScreen()
{
    writeSettings();
    delete ui;
}

bool LoginScreen::isLanGame()
{
    return ui->lanRadioButton->isChecked();
}

QString LoginScreen::username()
{
    return ui->nicknameLineEdit->text();
}

QString LoginScreen::password()
{
    return ui->passwdLineEdit->text();
}

void LoginScreen::on_backButton_clicked()
{
    emit backRequest();
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

void LoginScreen::on_playButton_clicked()
{
    if (ui->internetRadioButton->isChecked()
            && ui->passwdLineEdit->text().isEmpty()
            && !ui->anonymousCheckBox->isChecked()) {
        QMessageBox::warning(this, tr("Please fill password field"),
                             tr("Please provide password or"
                                " play as anonymous"));
        return;
    }

    emit playRequest();
}

void LoginScreen::writeSettings()
{
    QSettings settings;
    settings.beginGroup("LoginScreen");
    settings.setValue("internetRadioButton",
                      ui->internetRadioButton->isChecked());
    settings.setValue("nickname", ui->nicknameLineEdit->text());
    settings.setValue("anonymous", ui->anonymousCheckBox->isChecked());
    settings.setValue("password",
                      ui->storePasswdCheckBox->isChecked()
                      ? ui->passwdLineEdit->text()
                      : QString());
}

void LoginScreen::readSettings()
{
    QSettings settings;
    settings.beginGroup("LoginScreen");
    {
        bool internetRadioButton = settings.value("internetRadioButton",
                                                  ui->internetRadioButton
                                                  ->isChecked()).toBool();
        if (internetRadioButton)
            ui->internetRadioButton->setChecked(true);
        else
            ui->lanRadioButton->setChecked(true);
    }
    ui->nicknameLineEdit->setText(settings.value("nickname").toString());
    ui->anonymousCheckBox->setChecked(settings.value("anonymous",
                                                     ui->anonymousCheckBox
                                                     ->isChecked())
                                      .toBool());
    {
        QString passwd = settings.value("password").toString();
        if (!passwd.isEmpty()) {
            ui->storePasswdCheckBox->setChecked(true);
            ui->passwdLineEdit->setText(passwd);
        }
    }
}
