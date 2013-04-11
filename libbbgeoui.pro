#-------------------------------------------------
#
# Project created by QtCreator 2013-02-13T10:58:39
#
#-------------------------------------------------

QT       += webkit sql opengl

TARGET = libbbgeoui
TEMPLATE = lib

LIBS += -L../libbbgeo -llibbbgeo
include(../libbbgeo/libbbgeo.pri)

LIBS+=-lglut32
LIBS+=-Lc:\Glut32\

DEFINES += LIBBBGEOUI_LIBRARY

SOURCES += libbbgeoui.cpp \
    vsoilgraphicsview.cpp \
    vsoilgraphicsscene.cpp \
    q3dwebview.cpp \
    geoprofile2dgraphicsview.cpp \
    geoprofile2dgraphicsscene.cpp \
    subsoilgraphicsscene.cpp \
    vsoilglwidget.cpp

HEADERS += libbbgeoui.h\
        libbbgeoui_global.h \
    vsoilgraphicsview.h \
    vsoilgraphicsscene.h \
    q3dwebview.h \
    geoprofile2dgraphicsview.h \
    geoprofile2dgraphicsscene.h \
    subsoilgraphicsscene.h \
    vsoilglwidget.h

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xEBFF564F
    TARGET.CAPABILITY = 
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = libbbgeoui.dll
    addFiles.path = !:/sys/bin
    DEPLOYMENT += addFiles
}

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

OTHER_FILES += \
    libbbgeoui.pri

FORMS +=
