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
 * @details This class represents the main window of the password manager.
 * It provides functionality for:
 * 1. Managing stored passwords.
 * 2. Generating new passwords.
 * 3. Adding custom passwords.
 * 4. Searching and deleting passwords.
 * 5. Displaying passwords in a categorized manner.
 * 6. Copying passwords to clipboard.
 * 7. Customizing the appearance and settings of the program.
 *
 * The UI consists of several pages (Manage Passwords, Generate Passwords, Categories, Check Password, Settings)
 *                                   and a ListWidget to navigate between them.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Constructs the MainWindow object.
     * @param parent The parent widget (default is nullptr).
     */
    MainWindow(QWidget *parent = nullptr);

    /**
     * @brief Destroys the MainWindow object.
     */
    ~MainWindow();

    DatabaseManager databaseManager;          ///< Manages interactions with the password database.
    PasswordGenerator passwordGenerator;      ///< Handles password generation.

private slots:
    /**
     * @brief Switches the displayed page in the UI.
     * @param index The index of the page to switch to.
     */
    void changePage(int index);

    /// Handles password generation when the button is clicked.
    void on_generateButton_clicked();

    /// Clears the generated password and the name input field.
    void on_deletePassButton_clicked();

    /// Saves the generated password to the database.
    void on_savePassButton_clicked();

    /// Searches for a password by name and displays it.
    void on_findButton_clicked();

    /// Deletes the found password from storage.
    void on_deleteButton_clicked();

    /// Adds a custom password manually.
    void on_addPassButton_clicked();

    /// Displays the name of a password.
    void on_showButton_clicked();

    /// Displays all saved passwords in a table.
    void on_showAllButton_clicked();

    /// Copies the generated password to the clipboard.
    void on_copyBufferButton_clicked();

    /// Copies the found password to the clipboard.
    void on_copyFindedButton_clicked();

private:
    Ui::MainWindow *ui; ///< Pointer to the UI elements.

    MasterPassword masterPasswordHandler; ///< Handles master password verification.
    PasswordGenerator password_generator; ///< Handle password generator.
    DatabaseManager database; ///< Handle database connection.

    /// Applies additional visual settings to the list widget.
    void listWidgetSettings();

    /// Loads and sets images for copy buttons.
    void copyButtonsImages();

    /// Aligns UI elements to be properly centered.
    void allignCenter();

    /// Opens and applies a custom style file for UI appearance.
    void openStyleFile();

    /// Initializes application logic and state on startup.
    void startProgramm();
};

#endif // MAINWINDOW_H
