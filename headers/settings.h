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


#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QApplication>
#include <QMap>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTranslator>
#include <QDebug>


/**
 * @brief The Settings class. Manages application settings such as interface language.
 *
 * The Settings class provides functionality to load, save, and apply user preferences stored
 * in a JSON file, specifically the interface language. It also handles the loading of Qt translation
 * files (.qm) to support multilingual user interfaces.
 *
 * This class is part of the Cerberus Password Manager project.
 */
class Settings : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief Constructor for Settings.
     * @param parent The parent QObject, defaults to nullptr.
     *
     * Loads the current settings from the settings.json file upon construction.
     */
    explicit Settings(QObject* parent = nullptr);

    /**
     * @brief Destructor for Settings.
     */
    ~Settings();

    /**
     * @brief Gets the currently selected language.
     * @return The language as a QString (e.g., "English", "Russian", etc.).
     */
    QString getLanguage();

    /**
     * @brief Attempts to set the application language.
     * @param selectedLang The language to apply.
     * @return true if the language was successfully applied, false otherwise.
     *
     * This function loads the appropriate .qm file using QTranslator and installs it into the application.
     */
    bool setLanguage(QString selectedLang);

    /**
     * @brief Loads settings from the settings.json file.
     *
     * This function is called during construction to initialize the settings map.
     */
    void loadSettings();

    /**
     * @brief Saves the currently selected language to the settings.json file.
     * @param selectedLang The language to save.
     * @return true if the file was successfully written, false otherwise.
     *
     * Updates the "language" key under the "app" object in the JSON file.
     */
    bool saveLanguage(QString selectedLang);

private:
    /**
     * @brief Internal map to store setting key-value pairs.
     *
     * Currently used only to store the "language" key.
     */
    QMap<QString, QString> settings;
};

#endif // SETTINGS_H
