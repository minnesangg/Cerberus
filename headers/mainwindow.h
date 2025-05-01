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


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "headers/masterpassword.h"
#include "headers/database.h"
#include "headers/password_generator.h"
#include "headers/pwnedapichecker.h"
#include <QMessageBox>
#include <QInputDialog>
#include <QListWidgetItem>
#include <QListWidget>
#include <QFile>
#include <QClipboard>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QProcess>
#include <QSysInfo>
#include <QFileDialog>
#include <QTranslator>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/**
 * @brief The MainWindow class.
 *
 * @details This class represents the main window of the password manager application.
 * It provides the user with functionality for managing, generating, and customizing passwords in a secure way.
 * 
 * The class includes:
 * - Password management: storing, searching, deleting, and displaying passwords.
 * - Password generation: creating strong passwords with customizable parameters.
 * - Custom password addition: allows users to manually add passwords.
 * - User interface navigation and settings customization.
 * 
 * The UI consists of multiple pages such as:
 * - Manage Passwords: Where stored passwords can be displayed and managed.
 * - Generate Passwords: Interface for creating new passwords.
 * - Categories: For organizing passwords into different categories.
 * - Check Password: To verify if a password is secure.
 * - Settings: Customization of application preferences, themes, and languages.
 * 
 * The navigation between these pages is handled using a ListWidget.
 */
 class MainWindow : public QMainWindow
 {
     Q_OBJECT
 
 public:
     /**
      * @brief Constructs the MainWindow object.
      * 
      * Initializes the main window of the password manager. Sets up the UI and initializes
      * the password generator, database manager, and master password handler.
      * 
      * @param parent The parent widget (default is nullptr).
      */
     MainWindow(QWidget *parent = nullptr);
 
     /**
      * @brief Destroys the MainWindow object.
      * 
      * Cleans up any resources used by the MainWindow and its associated components.
      */
     ~MainWindow();
 
 private slots:

     /**
      * @brief Slot that handles the result of the password check.
      *
      * This method is called when the password check has completed. It evaluates
      * whether the entered password has been found in any data breaches. Depending
      * on the result, it updates the UI with a corresponding message:
      * - If the password has been found in breaches, it shows a warning message
      *   with the number of breaches and advises the user to change their password.
      * - If the password is safe, it displays a confirmation message indicating
      *   the password is not in any breaches.
      *
      * @param found Boolean value indicating whether the password was found in any breaches.
      * @param count The number of breaches where the password was found.
      */
     void onPasswordChecked(bool found, int count);

     /**
      * @brief Handles the result of password breach checks for all passwords.
      *
      * This method is called when a password check completes, updating the table
      * with the result of the breach check. If the password was found in breaches,
      * the count of breaches is displayed. If the password is safe, a "Safe ✅" message
      * is shown in the table. It also ensures proper cleanup by deleting the checker object.
      *
      * @param found Indicates whether the password was found in any breaches.
      * @param count The number of breaches the password was found in, if any.
      */
     void onAllPasswordChecked(bool found, int count);

     /**
      * @brief Sets up the table for displaying passwords and breach counts.
      *
      * This method initializes the table widget by setting the column count to 2,
      * configuring the column headers, and adjusting the header resizing modes.
      * It also hides the vertical header, disables selection and editing features
      * for the table cells.
      */
     void setupTable();

     /**
      * @brief Switches the displayed page in the UI.
      * 
      * This method is triggered when the user selects a different page in the navigation.
      * It updates the content displayed in the main window based on the selected page.
      * 
      * @param index The index of the page to switch to.
      */
     void changePage(int index);
 
     /**
      * @brief Handles password generation when the button is clicked.
      */
     void on_generateButton_clicked();
 
     /**
      * @brief Clears the generated password and the name input field.
      */
     void on_deletePassButton_clicked();
 
     /**
      * @brief Saves the generated password to the database.
      */
     void on_savePassButton_clicked();
 
     /**
      * @brief Searches for a password by name and displays it.
      */
     void on_findButton_clicked();
 
     /**
      * @brief Deletes the found password from storage.
      */
     void on_deleteButton_clicked();
 
     /**
      * @brief Adds a custom password manually.
      */
     void on_addPassButton_clicked();
 
     /**
      * @brief Displays the name of a password.
      */
     void on_showButton_clicked();
 
     /**
      * @brief Displays all saved passwords in a table.
      */
     void on_showAllButton_clicked();
 
     /**
      * @brief Copies the generated password to the clipboard.
      */
     void on_copyBufferButton_clicked();
 
     /**
      * @brief Copies the found password to the clipboard.
      */
     void on_copyFindedButton_clicked();

     /**
     * @brief Slot triggered when the user clicks the "Check" button.
     *
     * This method retrieves the password entered by the user in the input field,
     * creates an instance of the PwnedApiChecker class, and connects the
     * `passwordChecked` signal to the `onPasswordChecked` slot.
     * Then, it calls the `checkPassword` method to check the entered password
     * against the "Have I Been Pwned" API.
     */
     void on_apiButton_clicked();

     /**
     * @brief Initiates the password check process for all saved passwords.
     *
     * This method retrieves all saved passwords from the database, clears the
     * existing password table, and then checks each password for breaches using
     * the Have I Been Pwned API. If a password is found in breaches, it is added
     * to the table with the corresponding breach count. The table is displayed after
     * all passwords have been processed.
     */
     void on_checkAllPassButton_clicked();

     /**
     * @brief Clears all contents from the password table and resets the row count.
     *
     * This method clears the content in all cells of the password table and resets
     * the row count to 0, effectively clearing the displayed passwords and breach data.
     */
     void on_clearAllPassButton_clicked();

     /**
     * @brief Displays additional information in a message box.
     *
     * This method shows a message box with information about the integration of
     * the application with "Have I Been Pwned" when the user clicks the additional
     * info button.
     */
     void on_additInfoButton_clicked();

     /**
     * @brief Clears the content of the table and resets its row count.
     *
     * This method is called when the "Clear Table" button is clicked. It clears the contents
     * of the table (ui->showPassTable) and resets the number of rows to zero.
     */
     void on_clearTableButton_clicked();

     /**
     * @brief Sends an email with the path to the passwords database.
     *
     * This method is triggered when the "Send Gmail" button is clicked. It retrieves the Gmail
     * address from the input field, checks if it is empty, and if not, it prepares to send the
     * email using an external executable. The executable is determined based on the operating system
     * (Linux or Windows) and is passed the Gmail address and the path to the passwords database.
     *
     * @note If the input field is empty, a message will be displayed on the status bar.
     */
     void on_gmailSendButton_clicked();

     /**
     * @brief Handles the file selection for importing a new database.
     *
     * Opens a file dialog to let the user select a `.db` file. If a file is selected,
     * the current database connection is closed and removed, and the selected database
     * file is copied into the application directory. If a database with the same name already exists, it is overwritten.
     *
     * Displays a status message in the status bar to indicate success or failure.
     */
     void on_chooseFileButton_clicked(); 

     /**
     * @brief Shows information about data security.
     *
     * Displays a message box explaining that all passwords in the database
     * are encrypted before being stored or transmitted.
     */
     void on_backupInfoButton_clicked();

     /**
     * @brief Handles the click event of the "Send Gmail Backup" button.
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
     */
     void on_generateInfoButton_clicked();

     void on_languageButton_clicked();

 private:

     /**
     * @brief Total number of passwords that need to be checked.
     *
     * This variable holds the count of passwords that need to be checked against
     * the "Have I Been Pwned" database. It is initialized before the checking
     * process starts and is incremented during the check process.
     */
     int totalPasswordsToCheck;

     /**
     * @brief Number of passwords that have already been checked.
     *
     * This variable tracks the number of passwords that have already been checked
     * against the "Have I Been Pwned" database. It is updated each time a password
     * check is completed.
     */
     int passwordsChecked;

     /**
     * @brief A map that stores the row index for each PwnedApiChecker instance.
     *
     * This map associates a `PwnedApiChecker` instance with the row number in the
     * password table where its results should be displayed. The key is the
     * `PwnedApiChecker*`, and the value is the corresponding row index in the
     * password table.
     */
     QMap<PwnedApiChecker*, int> checkerRowMap;

     /**
      * @brief Pointer to the UI elements.
      */
     Ui::MainWindow *ui;
 
     /**
      * @brief Handles master password verification.
      */
     MasterPassword masterPasswordHandler;
 
     /**
      * @brief Handles password generation.
      */
     PasswordGenerator password_generator;
 
     /**
      * @brief Handles database connection.
      */
     DatabaseManager database;

    //QTranslator translator;
 
     /**
      * @brief Applies additional visual settings to the list widget.
      */
     void listWidgetSettings();
 
     /**
      * @brief Loads and sets images for the buttons.
      */
     void buttonsImages();
 
     /**
      * @brief Aligns UI elements to be properly centered.
      */
     void allignCenter();
 
     /**
      * @brief Opens and applies a custom style file for UI appearance.
      */
     void openStyleFile();

     void setupComboBox();
 
     /**
      * @brief Initializes application logic and state on startup.
      */
     void startProgramm();

     /**
     * @brief Handles the click event of the "Send Gmail Backup" button.
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
     */
    QString confirmOperation();
 };
 
#endif //MAINWINDOW_H
