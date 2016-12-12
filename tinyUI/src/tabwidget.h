#ifndef TABWIDGET_H
#define TABWIDGET_H

#include "api_global.h"
#include <QTabWidget>
#include <QAction>
#include <QList>

#pragma execution_character_set("utf-8")

class ContentPane;
class APISHARED_EXPORT TabWidget : public QTabWidget
{
    Q_OBJECT
public:
    TabWidget(QWidget* parent = 0);
    ContentPane* getContentPane();
    int addTab(QWidget *page, const QString &label);

private:
    void changeActivePane();

protected:
    void dragEnterEvent(QDragEnterEvent *event) Q_DECL_OVERRIDE;
    void dragMoveEvent(QDragMoveEvent *event) Q_DECL_OVERRIDE;
    void dropEvent(QDropEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

private slots:
    void splitLeft();
    void splitRight();
    void splitTop();
    void splitBottom();
    void openInSubwindow();
    void closePane();
    void closeTab(int idx);
    void onTabBarClicked(int idx);
};

#endif // TABWIDGET_H
