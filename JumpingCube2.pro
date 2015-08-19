!include("../Common/retroshare_plugin.pri"): error("Could not include file ../Common/retroshare_plugin.pri")

greaterThan(QT_MAJOR_VERSION, 4) {
	# Qt 5
	QT += widgets
}

exists($$[QMAKE_MKSPECS]/features/mobility.prf) {
  CONFIG += mobility
} else {
  QT += multimedia
}
CONFIG += qt uic qrc resources
MOBILITY = multimedia

DEPENDPATH += ../../retroshare-gui/src/temp/ui ../../libretroshare/src
INCLUDEPATH += ../../retroshare-gui/src/temp/ui ../../libretroshare/src
INCLUDEPATH += ../../retroshare-gui/src/retroshare-gui

#################################### Windows #####################################

linux-* {
	INCLUDEPATH += /usr/include
	LIBS += $$system(pkg-config --libs opencv)
}

win32 {
	LIBS_DIR = $$PWD/../../../libs
	LIBS += -L"$$LIBS_DIR/lib/opencv"

	OPENCV_VERSION = 249
	LIBS += -lopencv_core$$OPENCV_VERSION -lopencv_highgui$$OPENCV_VERSION -lopencv_imgproc$$OPENCV_VERSION -llibjpeg -llibtiff -llibpng -llibjasper -lIlmImf -lole32 -loleaut32 -luuid -lavicap32 -lavifil32 -lvfw32 -lz
}

QMAKE_CXXFLAGS *= -Wall

SOURCES = JumpingCube2Plugin.cpp               \
          services/p3JumpingCube2.cc           \
          services/rsJumpingCube2Items.cc \
    gui/NEMainpage.cpp \
    gui/JumpingCube2Notify.cpp \
    gui/paintwidget.cpp \
    gui/jumpingcubewindow.cpp

HEADERS = JumpingCube2Plugin.h                 \
          services/p3JumpingCube2.h            \
          services/rsJumpingCube2Items.h       \
          interface/rsJumpingCube2.h \
    gui/NEMainpage.h \
    gui/JumpingCube2Notify.h \
    gui/paintwidget.h \
    gui/jumpingcubewindow.h

#FORMS   = gui/AudioInputConfig.ui

TARGET = JumpingCube2

RESOURCES = gui/JumpingCube2_images.qrc


LIBS += -lspeex -lspeexdsp

FORMS += \
    gui/NEMainpage.ui \
    gui/jumpingcubewindow.ui
