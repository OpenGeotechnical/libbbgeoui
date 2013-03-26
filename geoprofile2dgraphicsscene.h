#ifndef GEOPROFILE2DGRAPHICSSCENE_H
#define GEOPROFILE2DGRAPHICSSCENE_H

#include <QGraphicsScene>
#include "geoprofile2d.h"
#include "datastore.h"

class GeoProfile2DGraphicsScene : public QGraphicsScene
{
public:
    GeoProfile2DGraphicsScene();
    ~GeoProfile2DGraphicsScene();

    void setProfile(GeoProfile2D* profile);
    void setDataStore(DataStore* ds) { m_dataStore = ds; }

private:
    GeoProfile2D* m_profile;
    DataStore* m_dataStore;
};

#endif // GEOPROFILE2DGRAPHICSSCENE_H
