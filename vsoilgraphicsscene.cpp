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

        double scale = 1000 / (zmax - zmin);

        //cm fit nicely with pixel sizes
        for (int i=zmin; i<=zmax; i++){
            if(i==0){
                addLine(-2*scale, -1*i*scale, 0, -1*i*scale, QPen(Qt::black));
                addLine(5*scale, -1*i*scale, 7*scale, -1*i*scale, QPen(Qt::black));
            }
            else if(i%5==0){
                addLine(-2*scale, -1*i*scale, 0, -1*i*scale, QPen(Qt::black));
                QGraphicsTextItem *txt = addText(QString("%1").arg(i), QFont("Helvetica", 0.3 *scale));
                txt->setPos(-2*scale, -1*i*scale);

            }else{
                addLine(-1*scale, -1*i*scale, 0, -1*i*scale, QPen(Qt::black));
            }
        }
        //iterate through all layers in a vsoil
        for(int i=0; i<m_vsoil->getSoilLayers()->count(); i++){
            VSoilLayer layer = m_vsoil->getSoilLayers()->at(i);
            SoilType *soilType = m_dataStore->getSoilTypeById(layer.soiltype_id);

            if(soilType==NULL){
                addRect(0, -1*scale * layer.zmax, 5*scale, (layer.zmax - layer.zmin) * scale,
                        QPen(Qt::black), QBrush(Qt::white));
            }else{
                double y = -1*scale * layer.zmax;
                double h = (layer.zmax - layer.zmin) * scale;
                addRect(0, -1*scale * layer.zmax, 5*scale, (layer.zmax - layer.zmin) * scale,
                        QPen(QColor(soilType->color())), QBrush(QColor(soilType->color())));                
                QGraphicsTextItem *txt = addText(QString("%1 (%2, %3) (%4, %5)").arg(soilType->name())
                                                 .arg(soilType->yDry())
                                                 .arg(soilType->ySat())
                                                 .arg(soilType->c())
                                                 .arg(soilType->phi()), QFont("Helvetica", 0.2 *scale));
                txt->setPos(0, y);
            }
            //display the top of the layer
            QGraphicsTextItem *txt = addText(QString("%1").arg(layer.zmax));
            txt->setPos(5.1*scale, -1*scale * layer.zmax - 0.2*scale);
            //display the bottom of the layer
            if(i==m_vsoil->getSoilLayers()->count()-1){
                QGraphicsTextItem *txt = addText(QString("%1").arg(layer.zmin));
                txt->setPos(5.1*scale, -1*scale * layer.zmin- 0.2*scale);
            }
        }
    }    
}

