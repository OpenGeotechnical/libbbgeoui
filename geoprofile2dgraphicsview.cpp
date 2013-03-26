#include "geoprofile2dgraphicsview.h"
#include <QWheelEvent>

GeoProfile2DGraphicsView::GeoProfile2DGraphicsView(QWidget *parent) :
    QGraphicsView(parent)
{
    setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
}

void GeoProfile2DGraphicsView::wheelEvent(QWheelEvent *event)
{
    double scaleFactor = 1.15; //How fast we zoom
    if(event->delta() > 0) {
        //Zoom in
        scale(scaleFactor, scaleFactor);
    } else {
        //Zooming out
        scale(1.0 / scaleFactor, 1.0 / scaleFactor);
    }
}
