#include "database.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QByteArray>
#include <QCoreApplication>
#include <QMessageBox>
#include <QSqlError>
#include "qaesencryption.h"
#include "masterpassword.h"

DatabaseManager::DatabaseManager() {}

QMap<QString, QString> DatabaseManager::getSavedPasswords() const {
    return savedPasswords;
}

void DatabaseManager::initDatabase(){
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(QCoreApplication::applicationDirPath() + "/passwords.db");

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
    MasterPassword master_password;
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

        QByteArray decryptedPassword;
        if (masterKey.size() == 16) {
            decryptedPassword = QAESEncryption::Decrypt(QAESEncryption::AES_128, QAESEncryption::CBC,
                                                        encryptedPassword, masterKey, iv);
        } else {
            decryptedPassword = QAESEncryption::Decrypt(QAESEncryption::AES_256, QAESEncryption::CBC,
                                                        encryptedPassword, masterKey, iv);
        }

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
    MasterPassword master_password;
    QByteArray masterKey =  master_password.getMasterPasswordHash();
    QByteArray IV =  master_password.generateIV(16);
    QByteArray encryptedPassword;
    if(masterKey.size()== 16){
        encryptedPassword = QAESEncryption::Crypt(QAESEncryption::AES_128, QAESEncryption::CBC,
                                                  password.toUtf8(), masterKey, IV);
    } else {
        encryptedPassword = QAESEncryption::Crypt(QAESEncryption::AES_256, QAESEncryption::CBC,
                                                  password.toUtf8(), masterKey, IV);
    }

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
}
