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


#include "headers/masterpassword.h"


MasterPassword::MasterPassword() {}

void MasterPassword::masterPassword(QString password){
    // добавить "соль"
    QByteArray hashedPass = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256);

    QSettings settings(QCoreApplication::applicationDirPath() + "/master_password.ini", QSettings::IniFormat);
    settings.setValue("MasterPasswordHash", QString(hashedPass.toHex()));
}


bool MasterPassword::verifyMasterPass(const QString &inputPass) {
    QByteArray inputHashed = QCryptographicHash::hash(inputPass.toUtf8(), QCryptographicHash::Sha256);
    QByteArray savedHashed = getMasterPasswordHash();

    return inputHashed == savedHashed;
}

bool MasterPassword::checkMasterPass(QString password) {
    QSettings settings(QCoreApplication::applicationDirPath() + "/master_password.ini", QSettings::IniFormat);

    if (!verifyMasterPass(password)) {
        QMessageBox::critical(this, "Error", "Wrong Master Password. Please try again.");
        return false;
    }

    return true;
}


QByteArray MasterPassword::getMasterPasswordHash() {
    QSettings settings(QCoreApplication::applicationDirPath() + "/master_password.ini", QSettings::IniFormat);
    QString savedHashedHex = settings.value("MasterPasswordHash", "").toString();

    if(savedHashedHex.isEmpty()){
        return QByteArray();
    }
    return QByteArray::fromHex(savedHashedHex.toUtf8());
}


QByteArray MasterPassword::generateIV(int size){
    QByteArray IV;
    IV.resize(size);
    for (int i = 0; i < size; ++i) {
        IV[i] = static_cast<char>(QRandomGenerator::global()->bounded(256));
    }

    return IV;
}
