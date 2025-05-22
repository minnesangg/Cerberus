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
 * saving new passwords with encryption, and deleting passwords. Also password have optional field "category".
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

    /**
     * @brief Loads distinct non-empty categories from the database into the local categories list.
     *
     * Queries the database for all unique categories assigned to passwords,
     * excluding null or empty values, and stores them in the `categories` member.
     */
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

    /**
     * @brief Returns the list of currently loaded categories.
     *
     * @return QStringList A list of category names as QStrings.
     */
    QStringList getCategories() const;

    /**
     * @brief Assigns a category to a password record in the database.
     *
     * Updates the `category` field of the password entry identified by its name.
     *
     * @param password The name of the password entry to update.
     * @param category The category to assign to the password.
     * @return true if the database update was successful; false otherwise.
     */
    bool bindCategoriesDB(QString password, QString category);

    /**
     * @brief Retrieves all passwords and their names for a given category.
     *
     * Decrypts the stored encrypted passwords using the master password hash,
     * cleans non-printable characters, and returns a list of name-password pairs.
     *
     * @param category The category to filter passwords by.
     * @return QVector<QPair<QString, QString>> Vector of pairs: password name and decrypted password string.
     */
    QVector<QPair<QString, QString>> getPasswordsByCategory(const QString& category);

    /**
     * @brief Adds a new category to the local categories list.
     *
     * Note: This does not update the database; it only modifies the in-memory list.
     *
     * @param newCategory The name of the category to add.
     */
    void addCategory(QString newCategory);

    /**
     * @brief Removes the association of a category from all passwords in the database.
     *
     * Sets the `category` field to NULL for all passwords assigned to the specified category.
     * Also removes the category from the local categories list.
     *
     * @param category The category to remove.
     * @return true if the database update was successful; false otherwise.
     */
    bool removeCategory(const QString& category);

private:
    QMap<QString, QString> savedPasswords;  ///< Stores passwords as (name, password) pairs.
    MasterPassword master_password;         ///< Object for handling the master password.
    QString dbPath; ///< Database path.
    QStringList categories; ///< Stores all categories for passwords.
};

#endif // DATABASE_H

