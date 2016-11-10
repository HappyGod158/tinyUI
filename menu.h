#ifndef MENU_H
#define MENU_H

#include "api_global.h"
#include <QObject>

enum ObjType{QMENU, QACTION};
class APISHARED_EXPORT Menu : public QObject
{
    Q_OBJECT
public:
    explicit Menu(QList<QString> path, QObject* obj, ObjType type, QObject *parent = 0);
    ~Menu();

    QList<QString>& getPath();

    QObject* getObj();

    ObjType getType();

private:
    QList<QString> path;
    QObject* obj;
    ObjType type;

signals:

public slots:
};

#endif // MENU_H
