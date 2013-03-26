#include <QGraphicsTextItem>
#include <QMessageBox>

#include "geoprofile2dgraphicsscene.h"
#include "soiltype.h"
#include "cmath"


GeoProfile2DGraphicsScene::GeoProfile2DGraphicsScene()
{
    m_profile = NULL;
    m_dataStore = NULL;
    setBackgroundBrush(Qt::white);
}

GeoProfile2DGraphicsScene::~GeoProfile2DGraphicsScene()
{
    m_profile = NULL;
    m_dataStore = NULL;
}

void GeoProfile2DGraphicsScene::setProfile(GeoProfile2D *profile)
{
    QFont serifFont("Times", 9);
    m_profile = profile;
    int lmin = 0;
    int lmax = m_profile->lMax();
    double zmax = m_profile->zMax();
    double zmin = m_profile->zMin();

    for(int i=0; i<m_profile->areas()->count(); i++){
        sArea l = m_profile->areas()->at(i);

        double lleft = l.start;
        double lright = l.end;

        //TODO: make sure m_dataStore is set! else exception
        VSoil* vs = m_dataStore->getVSoilById(l.vsoilId);
        //TODO: what if NULL?

        //iterate through all layers in a vsoil
        for(int j=0; j<vs->getSoilLayers()->count(); j++){
            VSoilLayer layer = vs->getSoilLayers()->at(j);
            SoilType *soilType = m_dataStore->getSoilTypeById(layer.soiltype_id);
            if(soilType==NULL){
                soilType = m_dataStore->getSoilTypeById(0); //default to dummy soiltype
            }
            addRect(lleft, -1 * layer.zmax, (lright-lleft), (layer.zmax - layer.zmin),
                    QPen(QColor(soilType->color())), QBrush(QColor(soilType->color())));            
        }
        QGraphicsTextItem *ti = addText(QString("%1").arg(vs->name()), serifFont);
        ti->setPos((lleft + lright) / 2, -1 * (zmax - zmin) / 2);
        ti->setFlag(QGraphicsItem::ItemIgnoresTransformations);
    }


    //and the depth lines and at least 0.
    int z1 = int((zmax > 0.) ? floor(zmax) : ceil(zmax));
    int z2 = int((zmin > 0.) ? floor(zmin) : ceil(zmin));
    int z = z1 > 0 ? int(ceil(z1 / 5)+1) * 5 : int(ceil(z1 / 5)) * 5;
    z1 = z;
    while(z >= (z2 - 5.)){
        addLine(lmin, -1*z, lmax, -1*z, QPen(Qt::DotLine));
        QGraphicsTextItem *ti = addText(QString("%1").arg(z), serifFont);
        ti->setPos(lmin - 5, -1*z);
        ti->setFlag(QGraphicsItem::ItemIgnoresTransformations);
        z -= 5;
    }
    z2 = z + 5; //yes, looks a bit dull this..

    //and now add the borders + distances
    for(int i=0; i<m_profile->areas()->count(); i++){
        sArea l = m_profile->areas()->at(i);
        double lleft = l.start;
        double lright = l.end;
        if(i==0){
            addLine(lleft, -1 * z1, lleft, -1 * z2, QPen(Qt::black));
            QGraphicsTextItem *ti = addText(QString("%1").arg(lleft), serifFont);
            ti->setPos(lleft, -1 * zmin);
            ti->setFlag(QGraphicsItem::ItemIgnoresTransformations);
        }
        addLine(lright, -1*z1, lright, -1 * z2, QPen(Qt::black));
        QGraphicsTextItem *ti = addText(QString("%1").arg(lright), serifFont);
        ti->setPos(lright, -1 * zmin);
        ti->setFlag(QGraphicsItem::ItemIgnoresTransformations);
    }

}
