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


#ifndef PWNEDAPICHECKER_H
#define PWNEDAPICHECKER_H

#include <QObject>
#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>
#include <QCryptographicHash>

/**
 * @class PwnedApiChecker
 * @brief A class that provides functionality for checking if a password has been exposed in a data breach.
 *
 * This class interacts with the "Have I Been Pwned" API to check whether a given password has been
 * part of any known data breaches. It hashes the password using SHA-1, sends the request to the API,
 * and emits a signal with the result indicating whether the password was found in any breaches.
 *
 * @note The API only checks if the password has been found in breaches by comparing the first
 * 5 characters of the SHA-1 hash. The exact matches are then checked from the response.
 */
class PwnedApiChecker : public QObject {
    Q_OBJECT

public:
    /**
     * @brief Constructor for PwnedApiChecker.
     *
     * Initializes the network manager to send HTTP requests.
     *
     * @param parent Optional parent object.
     */
    explicit PwnedApiChecker(QObject *parent = nullptr);

    /**
     * @brief Checks whether the given password has been exposed in a data breach.
     *
     * This method hashes the provided password using SHA-1 and sends a request to the "Have I Been Pwned"
     * API to check if the hashed password exists in their database. Upon receiving the response,
     * it will call the onFinished() method to handle the result.
     *
     * @param password The password to be checked.
     */
    void checkPassword(const QString &password);

private slots:
    /**
     * @brief Handles the response from the API and checks if the password was found in the breaches.
     *
     * This slot is invoked when the API request finishes. It processes the response, compares the suffix
     * of the hashed password, and determines if the password has been part of any known breaches.
     *
     * @param reply The network reply containing the response data.
     * @param hashSuffix The suffix of the password hash to check against the response.
     */
    void onFinished(QNetworkReply *reply, const QString &hashSuffix);

private:
    QNetworkAccessManager *manager; ///< Network manager for sending HTTP requests.

signals:
    /**
     * @brief Emitted when the password check is completed.
     *
     * This signal is emitted with the result of the password check, indicating whether the password
     * was found in any data breaches and how many times it was exposed.
     *
     * @param found Boolean value indicating whether the password was found in the breaches.
     * @param count The number of times the password was found in breaches.
     */
    void passwordChecked(bool found, int count);
};

#endif // PWNEDAPICHECKER_H
