#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../plugininterface.h"
#include "../pane.h"
#include <QLabel>

namespace Ui {
class MainWindow;
}

class QJsonObject;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    Ui::MainWindow* getUi();
    QLabel *getConnectivityLabel();

protected:
    void closeEvent(QCloseEvent *event);

private:
    Ui::MainWindow *ui;
    QLabel *connectivityLabel;
};

#endif // MAINWINDOW_H
