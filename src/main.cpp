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


#include <QApplication>
#include "headers/mainwindow.h"
#include "headers/dialoglogin.h"

/**
 * @brief The main entry point of the application.
 *
 * This function initializes the Qt application, first displaying a login dialog. If the user successfully logs in,
 * the main window is opened and the event loop is started.
 *
 * @param argc The number of command-line arguments.
 * @param argv The array of command-line arguments.
 * @return An integer indicating the exit status of the application (0 for success, non-zero for failure).
 */
int main(int argc, char *argv[])
{
    // Create a QApplication object, which is required for any Qt-based application
    QApplication app(argc, argv);

    // Create the login dialog
    DialogLogin login;

    // If the login dialog is accepted (user successfully logs in), open the main window
    if (login.exec() == QDialog::Accepted) {
        MainWindow window;

        // Set the size of the main window
        window.resize(1000, 700);

        // Set the stylesheet for the main window (background color)
        window.setStyleSheet("QMainWindow { background-color: #121212; }");

        // Set the window title
        window.setWindowTitle("Cerberus");

        // Set the application icon (ensure the path is correct)
        window.setWindowIcon(QIcon(":/icons/mainIcon.png"));

        // Display the main window
        window.show();

        // Start the application's event loop
        return app.exec();
    }

    // Return 0 if the login was not successful, indicating the application should not continue
    return 0;
}
