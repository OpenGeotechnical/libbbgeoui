#ifndef GEODESIGNERWIDGET_H
#define GEODESIGNERWIDGET_H

#include <QWidget>
#include "crosssectiongraphicsscene.h"
#include "watergraphicsscene.h"
#include "subsoilgraphicsscene.h"

namespace Ui {
class GeoDesignerWidget;
}

class GeoDesignerWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit GeoDesignerWidget(QWidget *parent = 0);
    ~GeoDesignerWidget();
    
private:
    Ui::GeoDesignerWidget *ui;
    CrossSectionGraphicsScene *m_crossSectionScene;
    WaterGraphicsScene *m_waterScene;
    SubSoilGraphicsScene *m_subSoilScene;

};

#endif // GEODESIGNERWIDGET_H
