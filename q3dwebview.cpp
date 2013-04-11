#include "q3dwebview.h"

#include <QDebug>
#include <QString>
#include <QWebSettings>
#include <QWebFrame>
#include <QMouseEvent>
#include "cmath"

#include "vsoilgraphicsscene.h"

#include "latlon.h"

#define MAP_HTML ""\
"<!DOCTYPE html>"\
"<html>"\
"  <head>"\
"    <title>Controling Google Maps through Qt application</title>"\
"    <meta name=\"viewport\""\
"        content=\"width=device-width, initial-scale=1.0, user-scalable=no\">"\
"    <meta charset=\"UTF-8\">"\
"    <style type=\"text/css\">"\
"      html, body, #map_canvas {"\
"        margin: 0;"\
"        padding: 0;"\
"        height: 100%;"\
"      }"\
"    </style>"\
"    <script type=\"text/javascript\" src=\"http://maps.googleapis.com/maps/api/js?sensor=false\"></script>"\
"    <script type=\"text/javascript\">"\
"      var map;"\
" "\
"      var myLatlng = new google.maps.LatLng(52.37, 4.895);"\
" "\
"      function initialize() {"\
"        var myOptions = {"\
"          zoom: 12,"\
"          center: new google.maps.LatLng(52.37, 4.895),"\
"          mapTypeId: google.maps.MapTypeId.HYBRID,"\
"          zoomControl: true,"\
"          zoomControlOptions: { style: google.maps.ZoomControlStyle.SMALL },"\
"        };"\
" "\
"        map = new google.maps.Map(document.getElementById('map_canvas'), myOptions);"\
"      }   "\
" "\
"      google.maps.event.addDomListener(window, 'load', initialize);"\
" "\
"    </script>"\
" "\
"  </head>"\
"  <body>"\
"    <div id=\"map_canvas\"></div>"\
"  </body>"\
"</html>"

q3DWebView::q3DWebView(QWidget *parent) : QWebView(parent)
{
    //enable Javacript interaction
    settings()->setAttribute(QWebSettings::JavascriptEnabled, true);    
    //enable memu popups
    //setContextMenuPolicy(Qt::DefaultContextMenu); //in linux the contextmenuevent does not seem to trigger.. so I handled it in the mouse release event
    m_mode = WVMODE_NORMAL;
    m_paintCPTLocations = true;
    m_paintVSoilLocations = true;

    m_actionAddVSoil = new QAction(tr("Add VSoil"), this);
    m_actionAddVSoil->setStatusTip(tr("Add a new VSoil on the chosen location."));
    m_mnuOptions = new QMenu(this);
    m_mnuOptions->addAction(m_actionAddVSoil);

    connect(m_actionAddVSoil, SIGNAL(triggered()), SLOT(addVSoil()));
}

void q3DWebView::init()
{
    //load the html
    setHtml(QString(MAP_HTML));
    //connect(this, SIGNAL(repaintRequested (QRect)), SLOT(updateBoundaries()));
}

void q3DWebView::updateBoundaries()
{
    double yb = page()->mainFrame()->evaluateJavaScript("map.getBounds().getSouthWest().lat()").toDouble();
    double yt = page()->mainFrame()->evaluateJavaScript("map.getBounds().getNorthEast().lat()").toDouble();
    double xr = page()->mainFrame()->evaluateJavaScript("map.getBounds().getNorthEast().lng()").toDouble();
    double xl = page()->mainFrame()->evaluateJavaScript("map.getBounds().getSouthWest().lng()").toDouble();

    m_boundary.setLeft(xl);
    m_boundary.setRight(xr);
    m_boundary.setTop(yt);
    m_boundary.setBottom(yb);
}

/*
 * Add a new vsoil to the datastore
 */
void q3DWebView::addVSoil()
{
    QPointF pointLatLon = windowPosToLatLon(m_mouseDownPosition);
    m_dataStore->addNewVSoil(pointLatLon, tr("manual"));
    emit(vsoilAdded(m_dataStore->getVSoils().count()-1)); //emit the signal so the mainwindow can display the vsoil dialog
}

void q3DWebView::paintEvent(QPaintEvent *event)
{
    updateBoundaries();

    QWebView::paintEvent(event);
    QPainter painter(this);
    QPen pen(Qt::green, 3, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin);
    QPen penText(Qt::black, 3);
    painter.setPen(pen);

    //paint the location of the visible cpt's
    if(m_paintCPTLocations){
        foreach(sCPTMetaData md, m_dataStore->getVisibleCPTs(m_boundary)){
            double lat = md.latitude;
            double lng = md.longitude;
            double x = (lng - m_boundary.x()) / m_boundary.width() * width();
            double y = (m_boundary.y() - lat) / (m_boundary.top() - m_boundary.bottom()) * height();

            painter.fillRect(int(x) - 2, int(y) - 2, 4, 4, QColor(0, 0, 255, 192));
        }
    }
    //paint the location of the visible vsoils
    if(m_paintVSoilLocations){
        foreach(VSoil *vs, m_dataStore->getVisibleVSoils(m_boundary)){
            //check if a filter is set and if so only show the filtered results
            if(m_vsoilSourceFilter=="All" ||  m_vsoilSourceFilter == vs->source()){
                double lat = vs->latitude();
                double lng = vs->longitude();
                double x = (lng - m_boundary.x()) / m_boundary.width() * width();
                double y = (m_boundary.y() - lat) / (m_boundary.top() - m_boundary.bottom()) * height();
                painter.fillRect(int(x) - 2, int(y) - 2, 4, 4, QColor(255, 0, 0, 192));
                if(m_mouseClosestToVSoilId == vs->id()){ //draw declarative text if the mouse is close to the point
                    painter.setPen(penText);
                    painter.drawText(int(x), int(y), QString("(%1) %2 - %3").arg(vs->id()).arg(vs->name()).arg(vs->source()));
                    painter.setPen(pen);
                    emit vsoilSelected(vs->id());
                }
            }            
        }
    }

    QPointF selectionLine[m_selection.count()];
    for(int i=0; i<m_selection.count(); i++){
        double lng = m_selection.at(i).x();
        double lat = m_selection.at(i).y();
        double x = (lng - m_boundary.x()) / m_boundary.width() * width();
        double y = (m_boundary.y() - lat) / (m_boundary.top() - m_boundary.bottom()) * height();
        selectionLine[i] = QPointF(x,y);
    }
    painter.drawPolyline(selectionLine, m_selection.count());
    QWebView::update();
}

void q3DWebView::mousePressEvent(QMouseEvent *evt)
{
    if (m_mode == WVMODE_NORMAL){
        QWebView::mousePressEvent(evt);
    }else if(m_mode == WVMODE_DRAW){ //adds a line to the selection path
        if(evt->button() == Qt::LeftButton){
            m_mouseDownPosition = evt->pos();
            addSelectedPoint(evt->pos());
        }
        else if(evt->button() == Qt::RightButton){ //right button = remove last point
            if(m_selection.count() > 0){
                m_selection.removeLast();
            }
        }
    }
}

void q3DWebView::mouseReleaseEvent(QMouseEvent *event)
{
    if(m_mode == WVMODE_NORMAL && event->button()==Qt::RightButton && m_dataStore->dataLoaded()){
        m_mouseDownPosition = event->globalPos();
        showContextMenu(event->globalPos());
    }
    QWebView::mouseReleaseEvent(event);
}

void q3DWebView::mouseMoveEvent(QMouseEvent *event)
{
    m_mouseClosestToVSoilId = -1;
    foreach(VSoil *vs, m_dataStore->getVisibleVSoils(m_boundary)){
        //check if a filter is set and if so only show the filtered results
        if(m_vsoilSourceFilter=="All" ||  m_vsoilSourceFilter == vs->source()){
            double lat = vs->latitude();
            double lng = vs->longitude();
            double x = (lng - m_boundary.x()) / m_boundary.width() * width();
            double y = (m_boundary.y() - lat) / (m_boundary.top() - m_boundary.bottom()) * height();

            if((x-3 < event->x()) && (event->x() < x+3) && (y-3 < event->y()) && (event->y() < y + 3)){
                m_mouseClosestToVSoilId = vs->id();
                break;
            }
        }
    }
    QWebView::mouseMoveEvent(event);
}



void q3DWebView::showContextMenu(QPoint p)
{
    m_mnuOptions->exec(p);
}

/*
    translate mouse x,y to map lat, lon
*/
QPointF q3DWebView::windowPosToLatLon(QPoint p){
    QPointF result;
    result.setX(m_boundary.x() + p.x() * m_boundary.width() / width());
    result.setY(m_boundary.y() + p.y() * m_boundary.height() / height());
    return result;
}

/*
    and vice versa
*/
QPoint q3DWebView::mapPosToWindowXY(QPointF p){
    QPoint result;
    //double d = ;
    result.setX(int(((p.x() - m_boundary.x()) / m_boundary.width()) * width()));
    result.setY(int(((p.y() - m_boundary.y()) / m_boundary.height()) * height()));
    return result;
}

void q3DWebView::addSelectedPoint(QPoint p){
    m_selection.append(windowPosToLatLon(p));
}

void q3DWebView::setMode(webviewMode mode)
{
    m_mode = mode;
}

void q3DWebView::removeSelection()
{
    m_selection.clear();
}

void q3DWebView::generate2DSoilProfile()
{
    //set the webview to the normal mode
    setMode(WVMODE_NORMAL);
    m_dataStore->generateGeoProfile2D(m_selection);
}

void q3DWebView::setVSoilSourceFilter(QString source)
{
    m_vsoilSourceFilter = source;
}
