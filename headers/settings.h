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
#include <memory>
#include <headers/inactivitywatcher.h>

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
     * @brief Returns the inactivity timer value from the settings.
     *
     * If the value is not set, returns the default "30000" (milliseconds).
     *
     * @return QString The inactivity timer as a string.
     */
    QString getTimer();

    /**
     * @brief Returns the login attempts limit from the settings.
     *
     * If the value is not set, returns the default "3".
     *
     * @return QString The login attempts limit as a string.
     */
    QString getAttempts();

    /**
     * @brief Attempts to set the application language.
     * @param selectedLang The language to apply.
     * @return true if the language was successfully applied, false otherwise.
     *
     * This function loads the appropriate .qm file using QTranslator and installs it into the application.
     */
    bool setLanguage(QString selectedLang);

    /**
     * @brief Sets the inactivity timer value.
     *
     * Converts the input string to an integer (milliseconds).
     * If conversion fails or the value is less than or equal to 9999 ms (10 секунд),
     * the function returns false.
     *
     * If the inactivity watcher is not created yet, it initializes it with the new timeout
     * and starts watching. Otherwise, it updates the existing watcher's timeout.
     *
     * @param timer The inactivity timer value as a string (milliseconds).
     * @return true If the timer was successfully set and valid.
     * @return false If the timer value is invalid or too low.
     */
    bool setTimer(const QString& timer);

    /**
     * @brief Sets the allowed number of login attempts.
     *
     * Converts the input string to an integer.
     * Returns false if conversion fails or if the attempts count is less than or equal to 2.
     *
     * @param attempts The login attempts limit as a string.
     * @return true If the attempts count is valid.
     * @return false If the attempts count is invalid or too low.
     */
    bool setAttempts(const QString& attempts);

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

    /**
     * @brief Saves the inactivity timer value to the settings.json file.
     *
     * Opens the settings.json file, reads the current JSON content,
     * updates the "timerInactivity" -> "timer" field with the provided value,
     * and writes the updated JSON back to the file.
     * Also updates the internal settings map.
     *
     * @param timer The inactivity timer value as a QString (milliseconds).
     * @return true if the file was successfully opened and written; false otherwise.
     */
    bool saveTimer(const QString& timer);

    /**
     * @brief Saves the login attempts limit value to the settings.json file.
     *
     * Opens the settings.json file, reads the current JSON content,
     * updates the "loginAttempts" -> "attempts" field with the provided value,
     * and writes the updated JSON back to the file.
     * Also updates the internal settings map.
     *
     * @param attempts The login attempts limit as a QString.
     * @return true if the file was successfully opened and written; false otherwise.
     */
    bool saveAttempts(const QString& attempts);

private:
    /**
     * @brief Internal map to store setting key-value pairs.
     *
     * Currently used only to store the "language" key.
     */
    QMap<QString, QString> settings;

    /**
     * @brief Unique pointer managing the InactivityWatcher instance.
     *
     * This smart pointer holds the InactivityWatcher object responsible for
     * monitoring user inactivity and triggering a timeout action.
     *
     * The use of std::unique_ptr ensures automatic resource management,
     * deleting the watcher when the owner (e.g., Settings) is destroyed or
     * when the pointer is reset.
     */
    std::unique_ptr<InactivityWatcher> inactivityWatcher;

};

#endif // SETTINGS_H
