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

#include "headers/password_generator.h"

#ifdef Q_OS_WIN
#include <windows.h>
#include <bcrypt.h>
#pragma comment(lib, "bcrypt.lib")
#endif

PasswordGenerator::PasswordGenerator() {}

QByteArray PasswordGenerator::secureRandomBytes(int size) {
    QByteArray randomData;
    randomData.resize(size);

#ifdef Q_OS_WIN
    BCRYPT_ALG_HANDLE hProvider = nullptr;
    if (BCryptOpenAlgorithmProvider(&hProvider, BCRYPT_RNG_ALGORITHM, nullptr, 0) == 0) {
        BCryptGenRandom(hProvider, reinterpret_cast<UCHAR*>(randomData.data()), size, 0);
        BCryptCloseAlgorithmProvider(hProvider, 0);
    }
#else
    QFile urandom("/dev/urandom");
    if (urandom.open(QIODevice::ReadOnly)) {
        urandom.read(randomData.data(), size);
        urandom.close();
    }
#endif

    return randomData;
}

QString PasswordGenerator::passGeneration(int passwordSize) {
    const QString symbols = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    QByteArray randomBytes = secureRandomBytes(passwordSize);

    QString password;
    int symbolCount = symbols.length();

    for (int i = 0; i < passwordSize; ++i) {
        quint8 index = static_cast<quint8>(randomBytes[i]) % symbolCount;
        password += symbols.at(index);
    }

    return password;
}

QByteArray PasswordGenerator::generateIV(int size){
    QByteArray IV;
    IV.resize(size);
    for (int i = 0; i < size; ++i) {
        IV[i] = static_cast<char>(QRandomGenerator::global()->bounded(256)); 
    }

    return IV;
}

