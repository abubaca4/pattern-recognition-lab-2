QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

FORMS += \
    mainwindow.ui

OPENCV_INSTALL_PATH = C:\opencv_build\install

OPENCV_VERSION = 455

OPENCV_COMPILER_VERSION = vc16

LIBS += \
    -L$${OPENCV_INSTALL_PATH}\x64\$${OPENCV_COMPILER_VERSION}\lib \
    -lopencv_core$${OPENCV_VERSION} \
    -lopencv_imgproc$${OPENCV_VERSION} \
    -lopencv_highgui$${OPENCV_VERSION} \
    -lopencv_imgcodecs$${OPENCV_VERSION} \
    -lopencv_videoio$${OPENCV_VERSION} \
    -lopencv_video$${OPENCV_VERSION} \
    -lopencv_calib3d$${OPENCV_VERSION} \
    -lopencv_photo$${OPENCV_VERSION} \
    -lopencv_features2d$${OPENCV_VERSION}

INCLUDEPATH += \
    $${OPENCV_INSTALL_PATH}\include

DEPENDPATH += \
    $${OPENCV_INSTALL_PATH}\include

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    mainwindow.qrc
