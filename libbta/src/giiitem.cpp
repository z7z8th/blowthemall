#include "giiitem.h"
#include <QtDeclarative/QtDeclarative>

namespace libbta {
namespace Gii {

Item::Item(QDeclarativeItem *parent) :
    QDeclarativeItem(parent)
{
    setFlag(QGraphicsItem::ItemHasNoContents, false);
}

void Item::registerType()
{
    qmlRegisterType<Item>("Gii", 0, 1, "GiiItem");
}

} // namespace Gii
} // namespace libbta
