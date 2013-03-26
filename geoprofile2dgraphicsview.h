#ifndef GEOPROFILE2DGRAPHICSVIEW_H
#define GEOPROFILE2DGRAPHICSVIEW_H

#include <QGraphicsView>

class GeoProfile2DGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit GeoProfile2DGraphicsView(QWidget *parent = 0);

protected:
    virtual void wheelEvent(QWheelEvent *event);
    
signals:
    
public slots:
    
};

#endif // GEOPROFILE2DGRAPHICSVIEW_H
