#ifndef VSOILGLWIDGET_H
#define VSOILGLWIDGET_H

#include <QGLWidget>
#include "vsoil.h"
#include "datastore.h"
#include <GL/glut.h>

class VSoilGLWidget : public QGLWidget
{
public:
    VSoilGLWidget();
    ~VSoilGLWidget();
    void setVSoil(VSoil* vs);
    void setDataStore(DataStore* ds) { m_dataStore = ds; }

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    VSoil* m_vsoil;
    DataStore* m_dataStore;

};

#endif // VSOILGLWIDGET_H
