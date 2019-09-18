#-------------------------------------------------
#
# Project created by QtCreator 2019-07-26T15:13:40
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Demo
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    prevscreennumctrl.cpp \
    playmultiwindow.cpp \
    playframe.cpp \
    frmmain.cpp \
    treeview.cpp \
    vprevwindow.cpp \
    vprevmulitwindow.cpp

HEADERS += \
        mainwindow.h \
#    inc/ants_ipc_api.h \
    #inc/I8_PlaySDK.h \
#    inc/I8Eye_common_def.h \
   # inc/I8H_SDK.h \
    prevscreennumctrl.h \
    playmultiwindow.h \
    playframe.h \
    frmmain.h \
    treeview.h \
    vprevwindow.h \
    vprevmulitwindow.h

FORMS += \
        mainwindow.ui \
    prevscreennumctrl.ui \
    playmultiwindow.ui \
    playframe.ui \
    frmmain.ui \
    treeview.ui \
    vprevwindow.ui \
    vprevmulitwindow.ui
		
TRANSLATIONS = cloudbox_zh_CN.ts \
                cloudbox_en_CN.ts

# LIBS += E:\Demo\Demo\lib\I8_PlaySDK.lib \
#     E:\Demo\Demo\lib\I8H_SDK.lib \

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/ -lI8_PlaySDK
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/ -lI8_PlaySDK

INCLUDEPATH += $$PWD/inc
DEPENDPATH += $$PWD/inc

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/ -lI8H_SDK
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/ -lI8H_SDK

INCLUDEPATH += $$PWD/inc
DEPENDPATH += $$PWD/inc

RESOURCES += \
    imag.qrc

DISTFILES += \
    ../../背景图.png \
    ../iiii.png

