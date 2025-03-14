QT += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
LIBS += -L$$PWD/Qt-Secret/src/build/release -lQt-Secret1
LIBS += -L$$PWD/Qt-Secret/src/mini-gmp/src/build/release -lQt-Secret1

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    database.cpp \
    dialoglogin.cpp \
    main.cpp \
    mainwindow.cpp \
    masterpassword.cpp \
    password_generator.cpp


include ($$PWD/Qt-Secret/src/Qt-Secret.pri)

HEADERS += \
    database.h \
    dialoglogin.h \
    mainwindow.h \
    masterpassword.h \
    password_generator.h


FORMS += \
    dialoglogin.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icons.qrc \
    resources.qrc
