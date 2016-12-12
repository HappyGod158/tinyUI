#include "pane.h"
#include <QLabel>
#include <QHBoxLayout>
#include "containerpane.h"

Pane::Pane(QWidget* parent):QSplitter(parent)
{
}

bool Pane::isRootPane()
{
    QWidget *parent = parentWidget();
    if(parent == nullptr ||
            qobject_cast<Pane*>(parent) == nullptr)
        return true;
    return false;
}
