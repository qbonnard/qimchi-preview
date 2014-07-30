TEMPLATE = lib
CONFIG += plugin #c++11
QT += qml quick multimedia

DESTDIR = ../imports/Chilitags
TARGET = $$qtLibraryTarget(chilitagsplugin)

HEADERS += \
    chilitagsplugin.h \
    chilitagsdetection.h \
    chilitagsobject.h \
    chilitagssurface.h \
    transform.h

SOURCES += \
    chilitagsplugin.cpp \
    chilitagsdetection.cpp \
    chilitagssurface.cpp \
    chilitagsobject.cpp \
    transform.cpp

LIBS += -lopencv_core -lopencv_imgproc
LIBS += -lchilitags
QMAKE_CXXFLAGS += -std=c++11

target.path=$$DESTPATH
android {
    qmldir.path=/assets/imports/Chilitags
    qmldir.files=$$PWD/qmldir
} else {
    qmldir.path=$$DESTPATH
    qmldir.files=$$PWD/qmldir
}
qmldir.depends += FORCE
INSTALLS += target qmldir

OTHER_FILES += \
    android/AndroidManifest.xml \
    qmldir

# Default rules for deployment.
include(deployment.pri)

#http://qt-project.org/forums/viewthread/41619

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

contains(ANDROID_TARGET_ARCH,armeabi-v7a) {
    INCLUDEPATH += $$PWD/android/include
    LIBS += -L$$PWD/android/libs/armeabi-v7a
    ANDROID_EXTRA_LIBS = \
        $$PWD/android/libs/armeabi-v7a/libopencv_core.so \
        $$PWD/android/libs/armeabi-v7a/libopencv_imgproc.so \
        $$PWD/android/libs/armeabi-v7a/libopencv_video.so \
        $$PWD/android/libs/armeabi-v7a/libopencv_highgui.so \
        $$PWD/android/libs/armeabi-v7a/libopencv_flann.so \
        $$PWD/android/libs/armeabi-v7a/libopencv_features2d.so \
        $$PWD/android/libs/armeabi-v7a/libopencv_calib3d.so \
        $$PWD/android/libs/armeabi-v7a/libchilitags.so
}

# Copy the qmldir file to the same folder as the plugin binary
QMAKE_POST_LINK += $$QMAKE_COPY $$replace($$list($$quote($$PWD/qmldir) $$DESTDIR), /, $$QMAKE_DIR_SEP)
