#-------------------------------------------------
#
# Project created by QtCreator 2018-12-28T09:49:30
#
#-------------------------------------------------

QT       += core gui network multimedia svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = redict
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    src/main.cpp \
    src/mainwindow.cpp \
    src/sidebar.cpp \
    src/sidebutton.cpp \
    src/youdaoapi.cpp \
    src/homepage.cpp \
    src/dictpage.cpp \
    src/dailypage.cpp \
    src/translatepage.cpp \
    src/aboutpage.cpp \
    src/utils.cpp \
    src/widgets/linkbutton.cpp \
    src/donatepage.cpp

HEADERS += \
    src/mainwindow.h \
    src/sidebar.h \
    src/sidebutton.h \
    src/youdaoapi.h \
    src/homepage.h \
    src/dictpage.h \
    src/dailypage.h \
    src/translatepage.h \
    src/aboutpage.h \
    src/utils.h \
    src/widgets/linkbutton.h \
    src/donatepage.h

TRANSLATIONS += translations/redict.ts \
                translations/redict_zh_CN.ts

RESOURCES += resources.qrc
