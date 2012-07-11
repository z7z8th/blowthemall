#include "gii_plugin.h"
#include "giiitem.h"

#include <qdeclarative.h>

void GiiPlugin::registerTypes(const char *uri)
{
    // @uri org.blowthemall.gii
    qmlRegisterType<GiiItem>(uri, 1, 0, "GiiItem");
}

Q_EXPORT_PLUGIN2(Gii, GiiPlugin)

