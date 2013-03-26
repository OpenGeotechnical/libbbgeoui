#ifndef VSOILGRAPHICSVIEW_H
#define VSOILGRAPHICSVIEW_H

#include <QGraphicsView>

class VSoilGraphicsView : public QGraphicsView
{
public:
    VSoilGraphicsView(QWidget *parent = 0);
protected:
    virtual void wheelEvent(QWheelEvent *event);
};

#endif // VSOILGRAPHICSVIEW_H
