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


#include "headers/database.h"
#include "qaesencryption.h"

DatabaseManager::DatabaseManager() {}

void DatabaseManager::deletePassword(const QString &name) {
    savedPasswords.remove(name);
}

QMap<QString, QString> DatabaseManager::getSavedPasswords() const {
    return savedPasswords;
}

void DatabaseManager::setDatabasePath(const QString& path){
    dbPath = path;
}

void DatabaseManager::initDatabase(){
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbPath);

    if (!db.open()) {
        QMessageBox::critical(this, "Database Error", db.lastError().text());
        return;
    }

    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS passwords ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "name TEXT UNIQUE, "
               "password TEXT)");
}

void DatabaseManager::loadPasswords() {
    savedPasswords.clear();

    QSqlQuery query;
    query.prepare("SELECT name, password FROM passwords");
    if (!query.exec()) {
        QMessageBox::critical(this, "Database Error", query.lastError().text());
        return;
    }

    while (query.next()) {
        QString name = query.value(0).toString();
        QByteArray encryptedData = query.value(1).toByteArray();
        QByteArray iv = encryptedData.left(16);
        QByteArray encryptedPassword = encryptedData.mid(16);
        QByteArray masterKey = master_password.getMasterPasswordHash();
        QByteArray decryptedPassword = QAESEncryption::Decrypt(QAESEncryption::AES_256, QAESEncryption::CBC, encryptedPassword, masterKey, iv);

        int endIndex = decryptedPassword.indexOf('\0');
        if (endIndex != -1) {
            decryptedPassword.truncate(endIndex);
        }

        QByteArray cleanedPassword;
        for (char c : decryptedPassword) {
            if (c >= 32 && c <= 126) {
                cleanedPassword.append(c);
            }
        }

        QString password = QString::fromUtf8(cleanedPassword);
        savedPasswords[name] = password;
    }
}

void DatabaseManager::savePassword(const QString &name, const QString &password) {
    QByteArray masterKey = master_password.getMasterPasswordHash();
    QByteArray IV = master_password.generateIV(16);
    QByteArray encryptedPassword = QAESEncryption::Crypt(QAESEncryption::AES_256, QAESEncryption::CBC, password.toUtf8(), masterKey, IV);

    if (encryptedPassword.isEmpty()) {
        QMessageBox::critical(this, "Encryption Error", "Failed to encrypt the password.");
        return;
    }

    QByteArray encryptedWithIV = IV + encryptedPassword;
    QSqlQuery query;
    query.prepare("INSERT OR REPLACE INTO passwords (name, password) VALUES (:name, :password)");
    query.bindValue(":name", name);
    query.bindValue(":password", encryptedWithIV);

    if (!query.exec()) {
        QMessageBox::critical(this, "Database Error", query.lastError().text());
    }
    savedPasswords[name] = password;
}

