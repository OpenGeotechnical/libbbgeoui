#include "geodesignerwidget.h"
#include "ui_geodesignerwidget.h"

GeoDesignerWidget::GeoDesignerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GeoDesignerWidget)
{
    ui->setupUi(this);
    m_crossSectionScene = new CrossSectionGraphicsScene();
    m_waterScene = new WaterGraphicsScene();
    m_subSoilScene = new SubSoilGraphicsScene();
}

GeoDesignerWidget::~GeoDesignerWidget()
{
    delete ui;
    delete m_crossSectionScene;
    delete m_waterScene;
    delete m_subSoilScene;
}
