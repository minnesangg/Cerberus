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


#ifndef PASSWORDGENERATOR_H
#define PASSWORDGENERATOR_H

#include <QString>
#include <QWidget>
#include <QMessageBox>
#include <QInputDialog>
#include <QRandomGenerator>
#include <QCryptographicHash>
#include <QFile>
#include <QSettings>


/**
 * @brief The PasswordGenerator class.
 *
 * @details This class is responsible for generating secure passwords and selecting the difficulty level
 * for password generation. It includes functionality for generating random passwords based on the selected
 * difficulty level and defining password size limits. Additionally, it can generate initialization vectors
 * (IV) used for encryption processes.
 */
class PasswordGenerator : public QWidget {
    Q_OBJECT

public:
    /**
     * @brief Constructs a PasswordGenerator object.
     *
     * @details Initializes a PasswordGenerator instance that can generate passwords and provide functionality
     * to choose difficulty levels for password creation.
     */
    PasswordGenerator();

    /**
     * @brief Generates a random password of the specified size.
     *
     * @details Generates a password by randomly selecting characters (uppercase and lowercase letters,
     * and digits) from a predefined set of symbols. The length of the password is determined by the
     * `passwordSize` parameter.
     *
     * @param passwordSize The length of the generated password.
     * @return A QString representing the generated password.
     */
    QString passGeneration(int passwordSize);

    /**
     * @brief Generates a random initialization vector (IV).
     *
     * @details Generates a random byte array of the specified size. This IV can be used for encryption
     * purposes to ensure randomness in cryptographic operations.
     *
     * @param size The size of the IV to be generated.
     * @return A QByteArray containing the generated IV.
     */
    QByteArray generateIV(int size);

    /**
     * @brief Generates cryptographically secure random bytes.
     *
     * This function generates a sequence of cryptographically secure random bytes
     * of the specified size.
     * On Windows, it uses `BCryptGenRandom` with `BCRYPT_RNG_ALGORITHM`.
     * On Unix-like systems, it reads directly from `/dev/urandom`.
     *
     * @param size The number of random bytes to generate.
     * @return QByteArray containing the generated random bytes.
     *
     * @note If the underlying random source fails, the returned QByteArray may contain uninitialized data.
     */
    QByteArray secureRandomBytes(int size);

};

#endif // PASSWORDGENERATOR_H

