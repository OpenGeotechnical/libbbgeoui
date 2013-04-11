#include "vsoilgraphicsscene.h"

#include <QDebug>
#include <QPainter>
#include <QGraphicsTextItem>

#include <cmath>

VSoilGraphicsScene::VSoilGraphicsScene()
{
    m_vsoil = NULL;
    m_dataStore = NULL;
}

VSoilGraphicsScene::~VSoilGraphicsScene()
{
    m_vsoil = NULL;
    m_dataStore = NULL;    
}

void VSoilGraphicsScene::setVSoil(VSoil *vs)
{
    m_vsoil = vs;
    generateScene();
}

void VSoilGraphicsScene::reloadScene()
{
    generateScene();
}

void VSoilGraphicsScene::generateScene()
{
    clear();

    if(m_vsoil==NULL){ qDebug() << "Error in VSoilGraphicsScene: m_vsoil = NULL!"; return; }
    if(m_dataStore==NULL) { qDebug() << "Error in VSoilGraphicsScene: m_dataStore = NULL!"; return; }

    if(m_vsoil != NULL){
        int zmax = ceil(m_vsoil->zMax());
        int zmin = floor(m_vsoil->zMin());
        if (zmax < 0) zmax = 0;

        for (int i=zmin; i<=zmax; i++){
            if(i==0){
                addLine(-2, -1*i, 0, -1*i, QPen(Qt::black));
                addLine(5, -1*i, 7, -1*i, QPen(Qt::black));
            }
            else if(i%5==0){
                addLine(-2, -1*i, 0, -1*i, QPen(Qt::black));
                //QGraphicsTextItem *txt = addText(QString("%1").arg(i));
                //txt->setPos(-2, -1*i);

            }else{
                addLine(-1, -1*i, 0, -1*i, QPen(Qt::black));
            }
        }
        //iterate through all layers in a vsoil
        for(int i=0; i<m_vsoil->getSoilLayers()->count(); i++){
            VSoilLayer layer = m_vsoil->getSoilLayers()->at(i);
            SoilType *soilType = m_dataStore->getSoilTypeById(layer.soiltype_id);

            if(soilType==NULL){
                addRect(0, -1 * layer.zmax, 5, (layer.zmax - layer.zmin),
                        QPen(Qt::black), QBrush(Qt::white));
            }else{
                addRect(0, -1 * layer.zmax, 5, (layer.zmax - layer.zmin),
                        QPen(QColor(soilType->color())), QBrush(QColor(soilType->color())));
            }
        }

    }    
}

