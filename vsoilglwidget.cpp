#include "vsoilglwidget.h"
#include <QtGui>
#include <QtOpenGL>

VSoilGLWidget::VSoilGLWidget()
{

}

VSoilGLWidget::~VSoilGLWidget()
{
    m_vsoil = NULL;
    m_dataStore = NULL;
}

void VSoilGLWidget::setVSoil(VSoil *vs)
{
    m_vsoil = vs;
}

void VSoilGLWidget::initializeGL()
{
    static const GLfloat lightPos[4] = { 5.0f, 5.0f, 10.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_NORMALIZE);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void VSoilGLWidget::paintGL()
{
    if(m_vsoil!=NULL){
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glPushMatrix();

        glPopMatrix();
    }
}

void VSoilGLWidget::resizeGL(int width, int height)
{
    int side = qMin(width, height);
    glViewport((width - side) / 2, (height - side) / 2, side, side);
}

void VSoilGLWidget::mousePressEvent(QMouseEvent *event)
{
}

void VSoilGLWidget::mouseMoveEvent(QMouseEvent *event)
{
}


