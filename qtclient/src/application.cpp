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

#include "application.h"
#include "mainwindow.h"
#include "mainscreen.h"
#include "loginscreen.h"
#include "settingsscreen.h"
#include "aboutscreen.h"

Application::Application(int &argc, char **argv) :
    QApplication(argc, argv)
{
    setOrganizationName("bombegman-dev"); // (?)
    setOrganizationDomain("blowthemall.googlecode.com");
    setApplicationName("BlowThemAll");

    // mainWindow may need to use the QSettings, so it
    // can't be initialized before the previous code
    mainWindow = new MainWindow;

    mainWindow->show();

    showMainScreen();
}

Application::~Application()
{
    delete mainWindow;
}

void Application::showMainScreen()
{
    MainScreen *mainScreen = new MainScreen;

    connect(mainScreen, SIGNAL(playRequest()), this, SLOT(showLoginScreen()));
    connect(mainScreen, SIGNAL(settingsRequest()), this, SLOT(showSettingsScreen()));
    connect(mainScreen, SIGNAL(aboutRequest()), this, SLOT(showAboutScreen()));
    connect(mainScreen, SIGNAL(quitRequest()), this, SLOT(quit()));

    mainWindow->setCentralWidget(mainScreen);
}

void Application::showLoginScreen()
{
    LoginScreen *loginScreen = new LoginScreen;

    connect(loginScreen, SIGNAL(backRequest()), this, SLOT(showMainScreen()));

    mainWindow->setCentralWidget(loginScreen);
}

void Application::showSettingsScreen()
{
    SettingsScreen *settingsScreen = new SettingsScreen;

    connect(settingsScreen, SIGNAL(backRequest()), this, SLOT(showMainScreen()));

    mainWindow->setCentralWidget(settingsScreen);
}

void Application::showAboutScreen()
{
    AboutScreen *aboutScreen = new AboutScreen;

    connect(aboutScreen, SIGNAL(backRequest()), this, SLOT(showMainScreen()));

    mainWindow->setCentralWidget(aboutScreen);
}
