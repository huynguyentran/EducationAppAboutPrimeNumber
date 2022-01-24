QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TARGET = EduApp

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bubble.cpp \
    bubblemanager.cpp \
    gameui.cpp \
    main.cpp \
    mainwindow.cpp \
    othersievewindow.cpp \
    primeinfo.cpp \
    sievesgame.cpp \
    sievewindow.cpp \
    welcomeanimation.cpp

HEADERS += \
    bubble.h \
    bubblemanager.h \
    gameui.h \
    mainwindow.h \
    othersievewindow.h \
    primeinfo.h \
    sievesgame.h \
    sievewindow.h \
    welcomeanimation.h

FORMS += \
    gameui.ui \
    mainwindow.ui \
    othersievewindow.ui \
    primeinfo.ui \
    sievewindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

unix|win32: LIBS += -L$$PWD/./ -lbox2d

INCLUDEPATH += $$PWD/box2d/include
DEPENDPATH += $$PWD/box2d/include

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/./box2d.lib
else:unix|win32-g++: PRE_TARGETDEPS += $$PWD/./libbox2d.a

win32:CONFIG(release, debug|release): LIBS += -LC:/packages/lib/ -lbox2d
else:win32:CONFIG(debug, debug|release): LIBS += -LC:/packages/lib/ -lbox2d
else:unix: LIBS += -LC:/packages/lib/ -lbox2d

INCLUDEPATH += C:/packages/include
DEPENDPATH += C:/packages/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/./ -lbox2d
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/./ -lbox2d
else:unix: LIBS += -L$$PWD/./ -lbox2d

INCLUDEPATH += $$PWD/box2d/include
DEPENDPATH += $$PWD/box2d/include

DISTFILES +=

RESOURCES += \
    res.qrc
