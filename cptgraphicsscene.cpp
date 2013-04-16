#include "cptgraphicsscene.h"
#include <QDebug>

CPTGraphicsScene::CPTGraphicsScene()
{
    m_cpt = NULL;
    m_dataStore = NULL;
}

CPTGraphicsScene::~CPTGraphicsScene()
{
    m_cpt = NULL;
    m_dataStore = NULL;
}

void CPTGraphicsScene::setCPT(CPT *cpt)
{
    m_cpt = cpt;
    generateScene();
}

void CPTGraphicsScene::generateScene()
{
    clear();

    if(m_cpt==NULL){ qDebug() << "Error in CPTGraphicsScene: m_cpt = NULL!"; return; }
    if(m_dataStore==NULL) { qDebug() << "Error in CPTGraphicsScene: m_dataStore = NULL!"; return; }

    if(m_cpt != NULL){
        double zmax = m_cpt->zmax();
        double zmin = m_cpt->zmin();
        for(int i=0; i<m_cpt->z()->count(); i++){

        }
    }
}
