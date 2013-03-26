#include "vsoilgraphicsview.h"
#include <QWheelEvent>

VSoilGraphicsView::VSoilGraphicsView(QWidget *parent)
{
    Q_UNUSED(parent);
    setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
}

void VSoilGraphicsView::wheelEvent(QWheelEvent *event)
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
