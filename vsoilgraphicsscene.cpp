#include "vsoilgraphicsscene.h"

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

    if(m_vsoil != NULL){
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

