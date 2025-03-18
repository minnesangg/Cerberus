#ifndef MASTERPASSWORD_H
#define MASTERPASSWORD_H

#include <QString>
#include <QByteArray>
#include <QSettings>
#include <QCryptographicHash>
#include <QWidget>
#include <QMessageBox>
#include <QInputDialog>
#include <QRandomGenerator>
#include <QCryptographicHash>
#include <QFile>
#include <QApplication>
#include <QSettings>
#include "headers/password_generator.h"

/**
 * @brief The MasterPassword class.
 *
 * @details This class is responsible for handling the master password for the password manager.
 * It provides functionality for setting and verifying the master password, generating a secure hash,
 * and creating initialization vectors for encryption. The class also interacts with other parts of the
 * system, such as the `PasswordGenerator`, to facilitate secure password management.
 * Master password hashes by SHA-256.
 */
class MasterPassword : public QWidget {
    Q_OBJECT

public:
    /**
     * @brief Constructs a MasterPassword object.
     */
    MasterPassword();

    /**
     * @brief Sets the master password.
     *
     * @details Hashes the provided password using SHA-256 and saves the result to a configuration file
     * (`master_password.ini`).
     *
     * @param password The master password to be set.
     */
    void masterPassword(QString password);

    /**
     * @brief Verifies if the input password matches the stored master password hash.
     *
     * @details Hashes the input password using SHA-256 and compares it with the stored hash in the
     * configuration file.
     *
     * @param inputPass The password entered by the user.
     * @return true if the password matches the stored hash, false otherwise.
     */
    bool verifyMasterPass(const QString &inputPass);

    /**
     * @brief Checks if the provided password is correct.
     *
     * @details Uses the `verifyMasterPass()` method to check if the entered password matches the
     * stored master password hash. Displays an error message if the password is incorrect.
     *
     * @param password The password to be checked.
     * @return true if the password is correct, false otherwise.
     */
    bool checkMasterPass(QString password);

    /**
     * @brief Retrieves the hash of the stored master password.
     *
     * @details Reads the stored master password hash from the configuration file and returns it as
     * a `QByteArray`. If no hash is found, returns an empty `QByteArray`.
     *
     * @return A `QByteArray` containing the hashed master password, or an empty `QByteArray` if no
     * password is stored.
     */
    QByteArray getMasterPasswordHash();

    /**
     * @brief Generates an initialization vector (IV) for encryption.
     *
     * @details Generates a random byte array of the specified size to be used as an IV in encryption
     * algorithms.
     *
     * @param size The size of the IV to be generated.
     * @return A `QByteArray` containing the generated IV.
     */
    QByteArray generateIV(int size);

private:
    PasswordGenerator password_generator; ///< Handles password generation.
};

#endif // MASTERPASSWORD_H
