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
