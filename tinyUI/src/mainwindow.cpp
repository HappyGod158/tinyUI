#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QTreeWidgetItem>
#include <QDebug>
#include <QDir>
#include <QPluginLoader>
#include <QDebug>
#include <QLabel>
#include <QDesktopWidget>
#include "workspace.h"
#include <QCloseEvent>
#include "settingmanager.h"

#pragma execution_character_set("utf-8")

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->treeWidget->setMaximumWidth(200);
    ui->splitter->setStretchFactor(0, 1);
    ui->splitter->setStretchFactor(1, 200);

    ContainerPane *rootPane = new ContainerPane();
    Workspace::getInstance().setRootPane(rootPane);

    ui->splitter->addWidget(rootPane);

    connectivityLabel = new QLabel();
    this->statusBar()->addPermanentWidget(connectivityLabel);
}

MainWindow::~MainWindow()
{
    delete ui;
}

Ui::MainWindow* MainWindow::getUi()
{
    return ui;
}

QLabel* MainWindow::getConnectivityLabel()
{
    return connectivityLabel;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    SettingManager::getInstance().writeSettings();
    event->accept();
}
