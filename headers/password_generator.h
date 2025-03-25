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

private:
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
};

#endif // PASSWORDGENERATOR_H