#ifndef CPTGRAPHICSSCENE_H
#define CPTGRAPHICSSCENE_H

#include <QGraphicsScene>

#include "cpt.h"
#include "datastore.h"

class CPTGraphicsScene : public QGraphicsScene
{
public:
    CPTGraphicsScene();
    ~CPTGraphicsScene();
    void setCPT(CPT* cpt);
    void setDataStore(DataStore* ds) { m_dataStore = ds; }

private:
    CPT* m_cpt;
    DataStore* m_dataStore;

    void generateScene();
};

#endif // CPTGRAPHICSSCENE_H
