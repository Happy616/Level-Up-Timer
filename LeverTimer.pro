QT       += core gui \
    quick

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Schedule.cpp \
    StatisticsWidget.cpp \
    TaskItem.cpp \
    TimerApp.cpp \
    board.cpp \
    main.cpp \
    mainwindow.cpp \
    mapp.cpp \
    userhome.cpp

HEADERS += \
    Schedule.h \
    StatisticsWidget.h \
    TaskDialog.h \
    TaskItem.h \
    TimerApp.h \
    board.h \
    mainwindow.h \
    mapp.h \
    userhome.h

FORMS += \
    board.ui \
    mainwindow.ui \
    mapp.ui \
    userhome.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
RC_ICONS = cat.ico

RESOURCES += \
    resourses.qrc
