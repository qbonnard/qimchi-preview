CONFIG += qt
QT += qml quick multimedia
TEMPLATE = lib
TARGET = qmlchilitags

HEADERS += \
    myvideosurface.h \
    frameobserver.h \
    chilitagscamera.h \
    chilitagsobject.h

SOURCES += \
    myvideosurface.cpp \
    chilitagscamera.cpp

LIBS += -lopencv_core -lopencv_imgproc
LIBS += -lchilitags

QMAKE_CXXFLAGS += -std=c++11
