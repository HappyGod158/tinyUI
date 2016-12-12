#ifndef GENERICPLUGIN_H
#define GENERICPLUGIN_H

#include "tinyui.h"
#include "page1.h"
#include "page2.h"
#include "page3.h"

class GenericPlugin : public QObject, PluginInterface
{
    Q_OBJECT
#if QT_VERSION >= 0x050000
    Q_PLUGIN_METADATA(IID "org.demo.PluginInterface" FILE "plugin1.json")
#endif // QT_VERSION >= 0x050000
    Q_INTERFACES(PluginInterface)
public:
    GenericPlugin();

    void initMenu() Q_DECL_OVERRIDE;
    void initSidebar() Q_DECL_OVERRIDE;
    void initPage() Q_DECL_OVERRIDE;

private slots:
    void onItemDoubleClicked(QTreeWidgetItem* item, int column);

private:
    QTreeWidgetItem* rootItem;
    QTreeWidgetItem* page1Item;
    QTreeWidgetItem* page2Item;
    QTreeWidgetItem* page3Item;

    Page1 *page1;
    Page2 *page2;
    Page3 *page3;

    QString page1Url;
    QString page2Url;
    QString page3Url;
};

#endif // GENERICPLUGIN_H
