QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
INCLUDEPATH += ./net
INCLUDEPATH += ./mediator
LIBS += -lws2_32

SOURCES += \
    chatdialog.cpp \
    ckernel.cpp \
    logindialog.cpp \
    main.cpp \
    mediator/INetMediator.cpp \
    mediator/TcpClientMediator.cpp \
    mychatdialog.cpp \
    net/TcpClient.cpp \
    useritem.cpp


HEADERS += \
    chatdialog.h \
    ckernel.h \
    logindialog.h \
    mediator/INetMediator.h \
    mediator/TcpClientMediator.h \
    mychatdialog.h \
    net/INet.h \
    net/PackDef.h \
    net/TcpClient.h \
    useritem.h



FORMS += \
    chatdialog.ui \
    logindialog.ui \
    mychatdialog.ui \
    useritem.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
CONFIG += console

RESOURCES += \
    resource.qrc

DISTFILES += \
    icon/1.jpeg \
    icon/2.png \
    icon/3.jpeg \
    icon/4.jpeg \
    icon/5.jpeg \
    icon/6.jpeg \
    icon/7.jpeg
