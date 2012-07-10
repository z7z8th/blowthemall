#ifndef RCC_H
#define RCC_H

#include <QtCore/QObject>

namespace Rcc {

    bool hasCompiler();
    bool compile(const QString &src, const QString &dst);

} // namespace RccCompiler

#endif // RCC_H
