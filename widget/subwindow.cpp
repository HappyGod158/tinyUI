#include "subwindow.h"
#include "ui_subwindow.h"
#include <QHBoxLayout>
#include "workspace.h"
#include "pagemanager.h"
#include <QCloseEvent>

SubWindow::SubWindow(QString &url, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SubWindow)
{
    ui->setupUi(this);

    deletePage = true;

    PageManager &pageManager = PageManager::getInstance();
    if(!pageManager.isPageInfoRegistered(url))
        return;


    label = pageManager.getPageInfo(url)->getLabel();
    this->url = url;

    bool rst = pageManager.constructPage(url, page);
    if(!rst)
        return;

    this->setWindowTitle(label);
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint & Qt::WindowMinMaxButtonsHint);
    this->setAttribute(Qt::WA_DeleteOnClose);
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(page);
    this->setLayout(layout);

    //构建action
    this->setContextMenuPolicy(Qt::ActionsContextMenu);

    QAction* backToWorkspaceAction = new QAction(tr("回到工作区"), this);
    this->addAction(backToWorkspaceAction);
    connect(backToWorkspaceAction, &QAction::triggered, this,  &SubWindow::backToWorkspace);
}

SubWindow::~SubWindow()
{
    delete ui;
}

void SubWindow::show()
{
    page->show();
    this->resize(500, 500);
    QDialog::show();
}

void SubWindow::backToWorkspace()
{
    Workspace &workspace = Workspace::getInstance();
    workspace.open(url);
    deletePage = false;
    this->close();
}

void SubWindow::closeEvent(QCloseEvent *event)
{
    if(deletePage){
        page->deleteLater();
        PageManager &pageManager = PageManager::getInstance();
        pageManager.unlinkPage(url);
    }
    event->accept();
}
