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

PasswordGenerator::PasswordGenerator() {}

QString PasswordGenerator::passGeneration(int passwordSize){
    char symbols[] = {
                      'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
                      'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
                      'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
                      'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
                      '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

    int symbolsSize = sizeof(symbols) / sizeof(symbols[0]);
    QString password;

    for (int i = 0; i < passwordSize; i++){
        int randomIndex = QRandomGenerator::global()->bounded(symbolsSize);
        password += symbols[randomIndex];
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

