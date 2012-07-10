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

#include "rcc.h"

#include <QtCore/QProcess>
#include <QtCore/QDir>

#ifndef RCC_TIMEOUT
#define RCC_TIMEOUT 10000
#endif

bool Rcc::hasCompiler()
{
    QString path = QProcessEnvironment::systemEnvironment().value("PATH");
#if Q_OS_WIN32
    QStringList searchDirectories = path.split(";");
#else
    QStringList searchDirectories = path.split(":");
#endif // Q_OS_WIN32

    for (QString d: searchDirectories) {
#if Q_OS_WIN32
        if (!QDir(d).entryList({"rcc.exe"}, QDir::Files).isEmpty()) {
#else
        if (!QDir(d).entryList({"rcc"}, QDir::Files | QDir::Executable)
                .isEmpty()) {
#endif // Q_OS_WIN32
            return true;
        }
    }

    return false;
}

bool Rcc::compile(const QString &src, const QString &dst)
{
#if Q_OS_WIN32
    QString program = "rcc.exe";
#else
    QString program = "rcc";
#endif // Q_OS_WIN32
    QProcess process;
    process.start(program, {"-binary", "-o", dst, src});

    if (!process.waitForFinished(RCC_TIMEOUT))
        return false;

    if (process.exitCode() != 0
            || process.exitStatus() != QProcess::NormalExit) {
        return false;
    }

    return true;
}
