#   Cerberus - Password Manager
#   Copyright (C) 2025 minnesang
#
#   This program is free software: you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation, either version 3 of the License, or
#   (at your option) any later version.
#
#   This program is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
#   GNU General Public License for more details.
#
#   You should have received a copy of the GNU General Public License
#   along with this program. If not, see <https://www.gnu.org/licenses/>.
#
QT += core gui sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# LIBS += -L/home/extra/programming/qt/Cerberus/Qt-Secret/src/build/release -lQt-Secret
# LIBS += -L/home/extra/programming/qt/Cerberus/Qt-Secret/src/mini-gmp/src/build/release -lQtBigInt
# QMAKE_RPATHDIR += /home/extra/programming/qt/Cerberus/Qt-Secret/src/build/release /home/extra/programming/qt/Cerberus/Qt-Secret/src/mini-gmp/src/build/release

win32:LIBS += -lbcrypt

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

contains(QMAKE_HOST_OS, "Windows") {
    message("Building for Windows")
    DEFINES += PLATFORM_WINDOWS
}

contains(QMAKE_HOST_OS, "Linux") {
    message("Building for Linux")
    DEFINES += PLATFORM_LINUX
}

DEFINES += QT_NO_QRESOURCE_COMPRESSION

SOURCES += \
    src/settings.cpp \
    src/database.cpp \
    src/dialoglogin.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/masterpassword.cpp \
    src/password_generator.cpp \
    src/pwnedapichecker.cpp

include ($$PWD/Qt-Secret/src/Qt-Secret.pri)

HEADERS += \
    headers/database.h \
    headers/dialoglogin.h \
    headers/mainwindow.h \
    headers/masterpassword.h \
    headers/password_generator.h \
    headers/pwnedapichecker.h \
    headers/settings.h

FORMS += \
    forms/dialoglogin.ui \
    forms/mainwindow.ui

TRANSLATIONS += translations/cerberus_ru.ts translations/cerberus_ua.ts translations/cerberus_en.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources/arrows.qrc \
   resources/icons.qrc \
    resources/optionsIcons.qrc \
    resources/resources.qrc \
    resources/translations.qrc
