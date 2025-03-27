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


#ifndef DIALOGLOGIN_H
#define DIALOGLOGIN_H

#include <QDialog>
#include <QString>
#include <QStackedWidget>
#include "headers/masterpassword.h"
#include <QMessageBox>
#include <QDebug>
#include <QFile>

namespace Ui {
class DialogLogin;
}

/**
 * @brief The DialogLogin class. Manages user authentication and master password setup.
 *
 * @details This class provides a login interface that allows users to authenticate
 * using a master password. If the master password is not yet set, it provides
 * an option to set a new one. The class handles switching between the login screen
 * and the new password setup screen, depending on whether a master password exists.
 */
class DialogLogin : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructs a DialogLogin object.
     *
     * @details Initializes the login dialog, sets up the UI, and checks if a master password
     * is already set. If not, it shows the option to set a new master password.
     *
     * @param parent The parent widget (default is nullptr).
     */
    explicit DialogLogin(QWidget *parent = nullptr);

    /**
     * @brief Destroys the DialogLogin object.
     *
     * @details Frees allocated resources.
     */
    ~DialogLogin();

private slots:
    /**
     * @brief Handles the login button click event.
     *
     * @details Checks the entered password against the stored master password.
     * If authentication succeeds, the dialog is accepted. If the password is incorrect or empty, it reduces the attempt count.
     * If the attempts run out, the application closes.
     */
    void on_loginButton_clicked();

    /**
     * @brief Handles the event when a new master password is being set.
     *
     * @details Saves the new master password and switches the UI to the login screen.
     */
    void on_newMasterPassButton_clicked();

private:
    Ui::DialogLogin *ui;                ///< UI elements for the dialog.
    QStackedWidget *masterPassStacked;  ///< Stack widget for switching between login and setup screens
        ///< based on whether a master password is set.
    MasterPassword master_pass;         ///< Object for handling master password authentication and management.
};

#endif // DIALOGLOGIN_H

