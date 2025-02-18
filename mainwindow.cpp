#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    databaseManager.initDatabase();
    databaseManager.loadPasswords();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_generateButton_clicked(){
    int begin = 0, min = 0, max = 0;
    bool ok;

    passwordGenerator.chooseDiff(begin, min, max, ok);
    if (!ok) return;

    int passwordSize = QInputDialog::getInt(this, tr("Generate Password"), tr("Choose password size:"), begin, min, max, 1, &ok);
    if (!ok) return;

    QString password = passwordGenerator.passGeneration(passwordSize);
    QMessageBox::information(this, "Generated Password", "Generated password: " + password);

    bool save = QMessageBox::question(this, "Save Password", "Do you want to save the password?") == QMessageBox::Yes;
    if (save){
        QString savedPass = QInputDialog::getText(this, "Save Password", "What is this password for?");
        if (!savedPass.isEmpty()){
            databaseManager.savePassword(savedPass, password);
            QMessageBox::information(this, "Password Saved", "Password saved successfully.");
        }
    }
    on_showButton_clicked();
}

void MainWindow::on_showButton_clicked() {
    databaseManager.loadPasswords();

    const auto& passwords = databaseManager.getSavedPasswords();
    if (passwords.isEmpty()) {
        QMessageBox::information(this, "Saved Passwords", "No saved passwords.");
        ui->passwordOutput->clear();
        return;
    }

    QString allPasswords;
    for (auto it = passwords.cbegin(); it != passwords.cend(); ++it) {
        allPasswords += "For " + it.key() + ": " + it.value() + "\n";
    }
    ui->passwordOutput->setPlainText(allPasswords);
}

void MainWindow::on_findButton_clicked() {
    QString key = QInputDialog::getText(this, "Find Password", "Which password do you need?");
    if (key.isEmpty()) return;

    const auto& passwords = databaseManager.getSavedPasswords();
    if (passwords.contains(key)) {
        QMessageBox::information(this, "Password Found", "Password for " + key + ": " + passwords.value(key));
    } else {
        QMessageBox::warning(this, "Not Found", "Password for " + key + " not found.");
    }
}

void MainWindow::on_deleteButton_clicked() {
    QString key = QInputDialog::getText(this, "Delete Password", "Which password do you want to delete?");
    if (key.isEmpty()) return;

    const auto& passwords = databaseManager.getSavedPasswords();
    if (!passwords.contains(key)) {
        QMessageBox::warning(this, "Not Found", "Password for " + key + " not found.");
        return;
    }

    if (databaseManager.deletePassword(key)) {
        QMessageBox::information(this, "Password Deleted", "Password for " + key + " has been deleted.");
        on_showButton_clicked();
    }
}

void MainWindow::on_addButton_clicked() {
    QString whichPassword = QInputDialog::getText(this, "Add Password", "Which password do you want to add?");
    if (whichPassword.isEmpty()) return;

    QString password = QInputDialog::getText(this, "Add Password", "Enter password:");
    if (password.isEmpty()) return;

    databaseManager.savePassword(whichPassword, password);
    QMessageBox::information(this, "Password Added", "Password added successfully.");
    on_showButton_clicked();
}

void MainWindow::on_clearButton_clicked(){
    ui->passwordOutput->clear();
}
