#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "masterpassword.h"
#include "database.h"
#include "password_generator.h"
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

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    DatabaseManager database;
    PasswordGenerator password_generator;

private slots:
    // void on_generateButton_clicked();
    // void on_showButton_clicked();
    // void on_findButton_clicked();
    // void on_deleteButton_clicked();
    // void on_addButton_clicked();
    // void on_clearButton_clicked();

    void changePage(int index);
    void on_generateButton_clicked();
    void on_deletePassButton_clicked();
    void on_copyBufferButton_clicked();
    void on_savePassButton_clicked();

    void on_findButton_clicked();

    void on_copyFindedButton_clicked();

    void on_deleteButton_clicked();

private:
    Ui::MainWindow *ui;
    MasterPassword masterPasswordHandler;
    DatabaseManager databaseManager;
    PasswordGenerator passwordGenerator;

    void MAKENAGAGREATAGAIN();
    void listWidgetSettings();
    void copyButtonsImages();

};

#endif // MAINWINDOW_H
