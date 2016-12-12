#ifndef SUBWINDOW_H
#define SUBWINDOW_H

#include <QDialog>

namespace Ui {
class SubWindow;
}

class SubWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SubWindow(QString& url, QWidget *parent = 0);
    ~SubWindow();
    void show();
    void closeEvent(QCloseEvent *event);

public slots:
    void backToWorkspace();

private:
    Ui::SubWindow *ui;
    QString url;
    QWidget *page;
    QString label;
    bool deletePage;
};

#endif // SUBWINDOW_H
