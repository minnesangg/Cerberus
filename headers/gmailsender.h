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

#ifndef GMAILSENDER_H
#define GMAILSENDER_H

#include <QString>
#include <QTranslator>
#include <QApplication>
#include <QWidget>
#include <QMessageBox>
#include "headers/masterpassword.h"
#include <QProcess>
#include <QStatusBar>

class GmailSender : public QWidget
{
    Q_OBJECT
public:
    GmailSender();

    /**
     * @brief Sends an email with the path to the passwords database.
     *
     * This method is triggered when the "Send Gmail" button is clicked. It retrieves the Gmail
     * address from the input field, checks if it is empty, and if not, it prepares to send the
     * email using an external executable. The executable is determined based on the operating system
     * (Linux or Windows) and is passed the Gmail address and the path to the passwords database.
     *
     * @param userGmail user gmail inputed in line.
     * @param statusbar statusbar pointer for printing operations status.
     *
     * @return returns true if operation is succesfull. otherwise return false.
     * @note If the input field is empty, a message will be displayed on the status bar.
     */
    bool sendGmail(const QString& userGmail, QStatusBar* statusBar);

    /**
     * @brief Handles the click event of the "Send Gmail Backup" button or of the "Change Master Password" button.
     *
     * This method validates the entered Gmail address, shows a confirmation dialog asking the user
     * if the email address is correct, and then prompts the user to enter the master password.
     * If the password is correct, it triggers the sending of a backup file to the provided Gmail address.
     * If the user cancels the operation or enters an incorrect password, an appropriate message is displayed.
     *
     * 1. Validates the Gmail input.
     * 2. Shows a warning dialog for email confirmation.
     * 3. Prompts the user to enter the master password for operation confirmation.
     * 4. Sends the backup file to the specified Gmail address if the password is correct.
     * 5. Displays error messages for incorrect password or operation cancellation.
     *
     * @return returns users master password.
     */
    QString confirmOperation();

private:
    MasterPassword masterPasswordHandler;
};

#endif // GMAILSENDER_H
