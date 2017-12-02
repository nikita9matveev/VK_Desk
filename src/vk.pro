#-------------------------------------------------
#
# Project created by QtCreator 2017-4-17T19:22:54
#
#-------------------------------------------------

QT += core gui network
QT += webkit
QT += webkitwidgets
QT += widgets

TARGET = vk
TEMPLATE = app

SOURCES += main.cpp\
        widget.cpp \
    vkconnect.cpp \
    form.cpp \
    w_login.cpp \
    myqtextedit.cpp \
    error_dialog.cpp \
    chat.cpp \
    crypt.cpp

HEADERS  += widget.h \
    vkconnect.h \
    form.h \
    w_login.h \
    myqtextedit.h \
    error_dialog.h \
    chat.h \
    crypt.h

FORMS    += widget.ui \
    form.ui \
    w_login.ui \
    myqtextedit.ui \
    error_dialog.ui

RESOURCES += \
    res.qrc

win32: LIBS += -L$$PWD/lib/ -lmyLib

INCLUDEPATH += $$PWD/lib
DEPENDPATH += $$PWD/lib
