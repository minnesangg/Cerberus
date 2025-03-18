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
     * @brief Selects the difficulty level for password generation.
     *
     * @details Displays a dialog allowing the user to choose the difficulty level for the password generation.
     * Based on the chosen difficulty, it adjusts the password size and sets limits for the password length.
     *
     * @param begin The starting length for the password.
     * @param min The minimum length for the password.
     * @param max The maximum length for the password.
     * @param ok A flag indicating if the user confirmed the selection.
     */
    void chooseDiff(int &begin, int &min, int &max, bool &ok);

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
