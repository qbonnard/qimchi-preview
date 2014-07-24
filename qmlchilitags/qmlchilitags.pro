TEMPLATE = lib
CONFIG += plugin
QT += qml quick multimedia

DESTDIR = ../imports/Chilitags
TARGET = $$qtLibraryTarget(chilitagsplugin)

HEADERS += \
    chilitagsplugin.h \
    chilitagsdetection.h \
    chilitagsobject.h \

SOURCES += \
    chilitagsplugin.cpp \
    chilitagsdetection.cpp \

LIBS += -lopencv_core -lopencv_imgproc
LIBS += -lchilitags
QMAKE_CXXFLAGS += -std=c++11

target.path=$$DESTPATH
qmldir.files=$$PWD/qmldir
qmldir.path=$$DESTPATH
INSTALLS += target qmldir

OTHER_FILES += \
    qmldir

# Copy the qmldir file to the same folder as the plugin binary
QMAKE_POST_LINK += $$QMAKE_COPY $$replace($$list($$quote($$PWD/qmldir) $$DESTDIR), /, $$QMAKE_DIR_SEP)
