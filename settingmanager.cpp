#include "settingmanager.h"
#include <QSettings>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include "workspace.h"
#include <QCoreApplication>
#include "nexus.h"
#include <QDebug>

SettingManager* SettingManager::settingManager = nullptr;

SettingManager::SettingManager(QObject *parent) : QObject(parent)
{
    orgName = "tinyUI-Dev";
    appName = "tinyUI";
}

SettingManager& SettingManager::getInstance()
{
    if(!settingManager)
        settingManager = new SettingManager();
    return *settingManager;
}

void SettingManager::destroyInstance()
{
    if(settingManager){
        delete settingManager;
        settingManager = nullptr;
    }
}

void SettingManager::readSettings()
{
    QString &orgName = QCoreApplication::organizationName();
    QString &appName = QCoreApplication::applicationName();
    if(orgName.isEmpty())
        orgName = this->orgName;
    if(appName.isEmpty())
        appName = this->appName;
    QSettings settings(QSettings::Format::IniFormat, QSettings::Scope::UserScope, orgName, appName);

    MainWindow* mainWindow = Nexus::getInstance().getMainWindow();
    settings.beginGroup("MainWindow");
    mainWindow->resize(settings.value("size", QSize(400, 400)).toSize());
    mainWindow->move(settings.value("pos", QPoint(200, 200)).toPoint());

    QString& workspaceState = settings.value("workspace").toString();
    if(workspaceState.isEmpty())
        return;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(QByteArray(workspaceState.toStdString().c_str()));
    if(jsonDoc.isObject() == false){
        qDebug() << "no setting for workspace found!";
        return;
    }
    QJsonObject jsonObject = jsonDoc.object();
    reconstructWorkspace(jsonObject.value("subPanes").toArray());
    settings.endGroup();
}

void SettingManager::writeSettings()
{
    QString &orgName = QCoreApplication::organizationName();
    QString &appName = QCoreApplication::applicationName();
    if(orgName.isEmpty())
        orgName = this->orgName;
    if(appName.isEmpty())
        appName = this->appName;
    QSettings settings(QSettings::Format::IniFormat, QSettings::Scope::UserScope, orgName, appName);
    settings.beginGroup("MainWindow");

    MainWindow* mainWindow = Nexus::getInstance().getMainWindow();
    settings.setValue("size", mainWindow->size());
    settings.setValue("pos", mainWindow->pos());

    Workspace& workspace = Workspace::getInstance();
    ContainerPane* rootPane = workspace.getRootPane();
    QJsonObject& rootPaneState = rootPane->serialize();
    QJsonDocument jsonDoc(rootPaneState);
    QString jsonStr(jsonDoc.toJson(QJsonDocument::Compact));
    settings.setValue("workspace", jsonStr);

    settings.endGroup();
}

void SettingManager::reconstructWorkspace(QJsonArray& subPanes)
{
    Workspace& workspace = Workspace::getInstance();
    ContainerPane* rootPane = workspace.getRootPane();
    int count = subPanes.count();
    for(int i=0; i<count; i++){
        QJsonObject &subPane = subPanes.at(i).toObject();
        QString& type = subPane.value("type").toString();
        if(type == "ContainerPane"){
            Pane* pane = ContainerPane::deserialize(subPane);
            rootPane->addWidget(pane);
        }else if(type == "ContentPane"){
            Pane* pane = ContentPane::deserialize(subPane);
            rootPane->addWidget(pane);
        }
    }
}
