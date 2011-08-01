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

Application::Application(int &argc, char **argv) :
    QApplication(argc, argv)
{
    setOrganizationName("bombegman-dev"); // (?)
    setOrganizationDomain("blowthemall.googlecode.com");
    setApplicationName("BlowThemAll");

    // mainWindow may need to use the QSettings, so it
    // can't be initialized before the previous code
    mainWindow = new MainWindow;

    mainWindow->setCentralWidget(new MainScreen);
    mainWindow->show();
}

Application::~Application()
{
    delete mainWindow;
}
