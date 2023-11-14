QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    adminwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    window2.cpp \
    window2_1.cpp \
    window3.cpp

HEADERS += \
    adminwindow.h \
    mainwindow.h \
    window2.h \
    window2_1.h \
    window3.h

FORMS += \
    adminwindow.ui \
    mainwindow.ui \
    window2.ui \
    window2_1.ui \
    window3.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
