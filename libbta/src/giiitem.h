#ifndef LIBBTA_GII_ITEM_H
#define LIBBTA_GII_ITEM_H

#include <QtDeclarative/QDeclarativeItem>

namespace libbta {
namespace Gii {

class Item : public QDeclarativeItem
{
    Q_OBJECT
    Q_PROPERTY(QString file
               READ file
               WRITE setFile
               NOTIFY fileChanged)
public:
    explicit Item(QDeclarativeItem *parent = 0);

    QString file();
    void setFile(const QString &file);

    static void registerType();
    
signals:
    void fileChanged();
    
public slots:
    
};

} // namespace Gii
} // namespace libbta

#endif // LIBBTA_GII_ITEM_H
