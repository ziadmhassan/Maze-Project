QT += core gui
QT += widgets
QT += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    boss.cpp \
    button.cpp \
    coin.cpp \
    enemy.cpp \
    main.cpp \
    map.cpp \
    player.cpp \
    shotgun.cpp \
    start.cpp

HEADERS += \
    boss.h \
    button.h \
    coin.h \
    enemy.h \
    map.h \
    player.h \
    shotgun.h \
    start.h

FORMS += \
    start.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
