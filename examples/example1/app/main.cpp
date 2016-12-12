#include <QApplication>
#include "tinyui.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setOrganizationName("org");
    QCoreApplication::setApplicationName("example1");

    Nexus::getInstance().getMainWindow()->setWindowTitle("demo");
    Nexus::getInstance().showMainWindow();

    QDir pluginsDir(qApp->applicationDirPath());
    if(!PluginManager::getInstance().loadPlugins(pluginsDir))
        qDebug() << "unable to load plugins";

    int returnCode = a.exec();
    return returnCode;
}
