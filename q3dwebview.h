#ifndef Q3DWEBVIEW_H
#define Q3DWEBVIEW_H

#include <QWebView>
#include <QList>
#include <QMenu>

#include "datastore.h"

enum webviewMode {WVMODE_NORMAL=1, WVMODE_DRAW, WVMODE_SELECT};

class q3DWebView : public QWebView
{
    Q_OBJECT
public:
    explicit q3DWebView(QWidget *parent = 0);

    void setDataStore(DataStore *dataStore) {m_dataStore = dataStore;}
    void init();
    void setDisplayCPTLocations(bool value) { m_paintCPTLocations = value; repaint(); }
    void setDisplayVSoilLocations(bool value) { m_paintVSoilLocations = value; repaint();}
    bool pointsSelected() { return m_selection.count() > 0; }
    int vsoilIdClosestToMouseLocation() { return m_mouseClosestToVSoilId; }
    void showContextMenu(QPoint p);

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    DataStore *m_dataStore;
    QRectF m_boundary;    
    webviewMode m_mode;
    QPoint m_mouseDownPosition;
    QList<QPointF> m_selection;
    QString m_vsoilSourceFilter;

    QMenu *m_mnuOptions;
    QAction *m_actionAddVSoil;
    int m_mouseClosestToVSoilId;


    bool m_paintCPTLocations; //if true, the cpt locations are plotted on the map
    bool m_paintVSoilLocations; //if true, the cpt locations are plotted on the map

    QPointF windowPosToLatLon(QPoint p);
    QPoint mapPosToWindowXY(QPointF p);

    void addSelectedPoint(QPoint p);

signals:
    void vsoilAdded(int);
    void vsoilSelected(int);
    
public slots:
    void setMode(webviewMode mode);
    void removeSelection();
    void generate2DSoilProfile();
    void setVSoilSourceFilter(QString source); //displays only vsoil with a source listed in sources

private slots:
    void updateBoundaries();
    void addVSoil();    
    
};

#endif // Q3DWEBVIEW_H
