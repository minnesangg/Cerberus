QT += core gui sql

QT += multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
LIBS += -L$$PWD/Qt-Secret/src/build/release -lQt-Secret1
LIBS += -L$$PWD/Qt-Secret/src/mini-gmp/src/build/release -lQt-Secret1

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/database.cpp \
    src/dialoglogin.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/masterpassword.cpp \
    src/password_generator.cpp


include ($$PWD/Qt-Secret/src/Qt-Secret.pri)

HEADERS += \
    headers/database.h \
    headers/dialoglogin.h \
    headers/mainwindow.h \
    headers/masterpassword.h \
    headers/password_generator.h


FORMS += \
    forms/dialoglogin.ui \
    forms/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources/arrows.qrc \
    resources/icons.qrc \
    resources/optionsIcons.qrc \
    resources/resources.qrc
