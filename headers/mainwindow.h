#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "headers/masterpassword.h"
#include "headers/database.h"
#include "headers/password_generator.h"
#include <QMessageBox>
#include <QInputDialog>
#include <QListWidgetItem>
#include <QListWidget>
#include <QFile>
#include <QClipboard>
#include <QTimer>
#include <QMediaPlayer>
#include <QVideoWidget>

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
 
     /**
      * @brief Manages interactions with the password database.
      */
     DatabaseManager databaseManager;
 
     /**
      * @brief Handles password generation.
      */
     PasswordGenerator passwordGenerator;
 
 private slots:
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
 
 private:
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
 
     /**
      * @brief Applies additional visual settings to the list widget.
      */
     void listWidgetSettings();
 
     /**
      * @brief Loads and sets images for the copy buttons.
      */
     void copyButtonsImages();
 
     /**
      * @brief Aligns UI elements to be properly centered.
      */
     void allignCenter();
 
     /**
      * @brief Opens and applies a custom style file for UI appearance.
      */
     void openStyleFile();
 
     /**
      * @brief Initializes application logic and state on startup.
      */
     void startProgramm();
 };
 
#endif //MAINWINDOW_H
