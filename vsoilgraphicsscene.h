#ifndef VSOILGRAPHICSSCENE_H
#define VSOILGRAPHICSSCENE_H

#include <QGraphicsScene>

#include "vsoil.h"
#include "datastore.h"

class VSoilGraphicsScene : public QGraphicsScene
{
public:
    VSoilGraphicsScene();
    ~VSoilGraphicsScene();
    void setVSoil(VSoil* vs);
    void setDataStore(DataStore* ds) { m_dataStore = ds; }    

    void reloadScene();

private:
    VSoil* m_vsoil;
    DataStore* m_dataStore;

    void generateScene();
};

#endif // VSOILGRAPHICSSCENE_H
