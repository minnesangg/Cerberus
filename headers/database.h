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


#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QByteArray>
#include <QString>
#include <QCoreApplication>
#include <QMessageBox>
#include <QMap>
#include "headers/masterpassword.h"

/**
 * @brief The DatabaseManager class.
 *
 * @details This class manages database operations for securely storing, loading, and deleting passwords.
 * It handles all database interactions, including AES-256 encryption and decryption of passwords
 * and stores them in a SQLite database. The passwords are associated with a name or label (e.g., website name)
 * for easy retrieval. This class also handles the initialization of the database, loading all stored passwords,
 * saving new passwords with encryption, and deleting passwords.
 *
 * @note Encryption is performed using AES-256 in CBC mode.
 */
class DatabaseManager : public QWidget {
    Q_OBJECT

public:
    /**
     * @brief Constructs a DatabaseManager object.
     *
     * @details Initializes the object but does not establish a database connection.
     * The database connection will be established later using `initDatabase()`.
     */
    DatabaseManager();

    /**
     * @brief Sets the path to the database file.
     *
     * This method stores the path to the SQLite database file,
     * which will be used by the application to open and manage the database.
     *
     * @param path The absolute or relative path to the SQLite database file.
     */
    void setDatabasePath(const QString& path);

    /**
     * @brief Initializes the database connection.
     *
     * @details Ensures that the database is accessible and ready for operations.
     * If the database does not exist, it creates a new SQLite database file.
     * It also creates a table for storing passwords.
     */
    void initDatabase();

    /**
     * @brief Loads all stored passwords from the database.
     *
     * @details Retrieves all saved passwords from the database, decrypts them
     * using the master password, and stores them in the `savedPasswords` QMap for quick access.
     */
    void loadPasswords();

    void loadCategories();

    /**
     * @brief Saves a password to the database.
     *
     * @details Encrypts the password using AES-256 and stores it in the database with a name or label.
     * If the password already exists, it updates the existing record.
     *
     * @param name The name or label associated with the password (e.g., website name).
     * @param password The password to be stored (it will be encrypted before saving).
     */
    void savePassword(const QString &name, const QString &password);

    /**
     * @brief Deletes a password from the database.
     *
     * @details Removes the password entry identified by the provided name from the database.
     *
     * @param name The name of the password entry to be removed.
     */
    void deletePassword(const QString &name);

    /**
     * @brief Retrieves all saved passwords.
     *
     * @details Returns a QMap containing pairs of password names and their corresponding values.
     *
     * @return A QMap containing (name, password) pairs for all saved passwords.
     */
    QMap<QString, QString> getSavedPasswords() const;

    QStringList getCategories() const;

    bool bindCategoriesDB(QString password, QString category);

    QVector<QPair<QString, QString>> getPasswordsByCategory(const QString& category);

    void addCategory(QString newCategory);

    bool removeCategory(const QString& category);

private:
    QMap<QString, QString> savedPasswords;  ///< Stores passwords as (name, password) pairs.
    MasterPassword master_password;         ///< Object for handling the master password.
    QString dbPath; ///< Database path.
    QStringList categories; ///< Stores all categories for passwords.
};

#endif // DATABASE_H

