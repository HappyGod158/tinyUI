#include "containerpane.h"
#include "contentpane.h"
#include <QJsonObject>
#include <QJsonArray>

ContainerPane::ContainerPane(QWidget *parent):Pane(parent)
{
}

void ContainerPane::addPane(Pane *pane)
{
    addWidget(pane);
}

QJsonObject ContainerPane::serialize()
{
    QJsonObject paneState;
    QJsonArray subPaneArray;

    int count = this->count();
    for(int i=0; i<count; i++){
        ContainerPane* containerPane = qobject_cast<ContainerPane*>(widget(i));
        ContentPane* contentPane = qobject_cast<ContentPane*>(widget(i));
        if(containerPane){
            subPaneArray.append(containerPane->serialize());
        }else if(contentPane){
            subPaneArray.append(contentPane->serialize());
        }else
            return paneState;
    }

    Qt::Orientation orientation = this->orientation();
    QString paneName = "ContainerPane";
    paneState.insert("type", paneName);
    paneState.insert("orientation", orientation == Qt::Horizontal ? "Horizontal" : "Vertical");
    paneState.insert("subPanes", subPaneArray);

    QSize size = this->size();
    QJsonObject sizeObj;
    sizeObj.insert("width", size.width());
    sizeObj.insert("height", size.height());
    paneState.insert("size", sizeObj);
    return paneState;
}

Pane* ContainerPane::deserialize(QJsonObject& jsonObj)
{
    QJsonValue orientation = jsonObj.value("orientation");
    ContainerPane* pane = new ContainerPane();
    pane->setOrientation(orientation == "Horizontal" ? Qt::Horizontal : Qt::Vertical);
    QJsonArray &subPanes = jsonObj.value("subPanes").toArray();
    int count = subPanes.count();

    for(int i=0; i<count; i++){
        QJsonObject& subPaneJsonObj = subPanes[i].toObject();
        QJsonValue type = subPaneJsonObj.value("type");
        if(type.toString() == "ContainerPane"){
            Pane* tmp = ContainerPane::deserialize(subPaneJsonObj);
            if(tmp)
                pane->addWidget(tmp);
        }else if(type.toString() == "ContentPane"){
            Pane* tmp = ContentPane::deserialize(subPaneJsonObj);
            if(tmp)
                pane->addWidget(tmp);
        }
    }

    QJsonObject &sizeObj = jsonObj.value("size").toObject();
    QSize size;
    size.setWidth(sizeObj.value("width").toInt());
    size.setHeight(sizeObj.value("height").toInt());
    pane->resize(size);
    return pane;
}
