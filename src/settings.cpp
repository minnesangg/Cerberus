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
    QString lang, timer, attempts;
    if(file.open(QIODevice::ReadOnly)) {
        QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
        QJsonObject obj = doc.object();
        lang = obj["app"].toObject()["language"].toString();
        timer = obj["timerInactivity"].toObject()["timer"].toString();
        attempts = obj["loginAttempts"].toObject()["attempts"].toString();
    }
    settings["language"] = lang;
    settings["timerInactivity"] = timer;
    settings["loginAttempts"] = attempts;
}

bool Settings::saveLanguage(QString selectedLang) {
    QFile file("settings.json");
    if (!file.open(QIODevice::ReadWrite)) {
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

bool Settings::saveTimer(const QString& timer){
    QFile file("settings.json");
    if(!file.open(QIODevice::ReadWrite)) {
        return false;
    }

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    QJsonObject jsonObj = doc.object();

    QJsonObject timerObj = jsonObj["timerInactivity"].toObject();
    timerObj["timer"] = timer;
    jsonObj["timerInactivity"] = timerObj;

    file.resize(0);
    file.seek(0);
    file.write(QJsonDocument(jsonObj).toJson());

    settings["timerInactivity"] = timer;

    return true;
}

bool Settings::saveAttempts(const QString& attempts){
    QFile file("settings.json");
    if(!file.open(QIODevice::ReadWrite)) {
        return false;
    }

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    QJsonObject jsonObj = doc.object();

    QJsonObject attemptsObj = jsonObj["loginAttempts"].toObject();
    attemptsObj["attempts"] = attempts;
    jsonObj["loginAttempts"] = attemptsObj;

    file.resize(0);
    file.seek(0);
    file.write(QJsonDocument(jsonObj).toJson());

    settings["loginAttempts"] = attempts;

    return true;
}

QString Settings::getLanguage() {
    return settings["language"];
}

QString Settings::getTimer(){
    return settings.value("timerInactivity", "30000");
}

QString Settings::getAttempts(){
    return settings.value("loginAttempts", "3");
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

bool Settings::setTimer(const QString& timer) {
    bool ok = false;
    int timerInactivity = timer.toInt(&ok);

    if (!ok || timerInactivity <= 9999) {
        return false;
    }

    if (!inactivityWatcher) {
        inactivityWatcher = std::make_unique<InactivityWatcher>(nullptr, timerInactivity);
        inactivityWatcher->startWatching();
    } else {
        inactivityWatcher->updateTimeout(timerInactivity);
    }

    return true;
}

bool Settings::setAttempts(const QString& attempts){
    bool ok = false;
    int attemptsCounter = attempts.toInt(&ok);

    if(!ok || attemptsCounter <= 2){
        return false;
    }
    return true;
}
