#ifndef GII_PLUGIN_H
#define GII_PLUGIN_H

#include <QDeclarativeExtensionPlugin>

class GiiPlugin : public QDeclarativeExtensionPlugin
{
    Q_OBJECT
    
public:
    void registerTypes(const char *uri);
};

#endif // GII_PLUGIN_H

