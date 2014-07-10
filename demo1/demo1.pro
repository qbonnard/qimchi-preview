TEMPLATE = app

QT += qml quick

QT += multimedia
QMAKE_CXXFLAGS += -std=c++11
LIBS += -L../qmlchilitags -lqmlchilitags

SOURCES += main.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)
