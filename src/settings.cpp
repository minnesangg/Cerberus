/*
 * Cerberus - Password Manager
 * Copyright (C) 2025 minnesang
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 */


#include "headers/settings.h"

Settings::Settings(QObject* parent) : QObject(parent) {
    loadSettings();
}

Settings::~Settings() {}

void Settings::loadSettings() {
    QFile file("settings.json");
    QString lang;
    if(file.open(QIODevice::ReadOnly)) {
        QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
        QJsonObject obj = doc.object();
        lang = obj["app"].toObject()["language"].toString();
    }
    settings["language"] = lang;
}

bool Settings::saveLanguage(QString selectedLang) {
    QFile file("settings.json");
    if (!file.open(QIODevice::ReadWrite)) {
        qDebug() << "Failed to open settings.json for writing!";
        return false;
    }

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    QJsonObject jsonObj = doc.object();

    QJsonObject appObj = jsonObj["app"].toObject();
    appObj["language"] = selectedLang;

    jsonObj["app"] = appObj;

    file.resize(0);
    QJsonDocument newDoc(jsonObj);
    file.write(newDoc.toJson());

    return true;
}

QString Settings::getLanguage() {
    return settings["language"];
}

bool Settings::setLanguage(QString selectedLang) {
    static QTranslator* translator = nullptr;

    QMap<QString, QString> langMap = {
        {"English", ":/translations/cerberus_en.qm"},
        {"Russian", ":/translations/cerberus_ru.qm"},
        {"Ukrainian", ":/translations/cerberus_ua.qm"}
    };

    if (!langMap.contains(selectedLang)) {
        return false;
    }

    if (translator) {
        qApp->removeTranslator(translator);
        delete translator;
        translator = nullptr;
    }

    translator = new QTranslator(qApp);
    QString translationFile = langMap[selectedLang];

    if (translator->load(translationFile)) {
        qApp->installTranslator(translator);
        return true;
    } else {
        delete translator;
        translator = nullptr;
        return false;
    }
}

