#include "menu.h"

Menu::Menu(QList<QString> path, QObject* obj, ObjType type, QObject *parent) : QObject(parent)
{
    this->path = path;
    this->obj = obj;
    this->type = type;
}

Menu::~Menu()
{
    delete obj;
}

QList<QString>& Menu::getPath()
{
   return path;
}


QObject* Menu::getObj()
{
    return obj;
}

ObjType Menu::getType()
{
    return type;
}


