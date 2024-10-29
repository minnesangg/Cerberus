#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QInputDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QRandomGenerator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initDatabase();
    loadPasswords();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initDatabase(){
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(QCoreApplication::applicationDirPath() + "/passwords.db");

    if (!db.open()) {
        QMessageBox::critical(this, "Database Error", db.lastError().text());
        return;
    }

    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS passwords ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "name TEXT UNIQUE, "
               "password TEXT)");
}

void MainWindow::loadPasswords(){
    savedPasswords.clear();
    QSqlQuery query("SELECT name, password FROM passwords");

    while (query.next()) {
        QString key = query.value(0).toString();
        QString value = query.value(1).toString();
        savedPasswords[key.toStdString()] = value.toStdString();
    }
}

void MainWindow::on_generateButton_clicked(){
    int begin = 0, min = 0, max = 0;
    bool ok;

    chooseDiff(begin, min, max, ok);
    if (!ok) return;

    int passwordSize = QInputDialog::getInt(this, tr("Generate Password"), tr("Choose password size:"), begin, min, max, 1, &ok);
    if (!ok) return;

    char symbols[] = {
                      'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
                      'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
                      'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
                      'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
                      '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

    int symbolsSize = sizeof(symbols) / sizeof(symbols[0]);
    QString password;

    for (int i = 0; i < passwordSize; i++){
        int randomIndex = QRandomGenerator::global()->bounded(symbolsSize);
        password += symbols[randomIndex];
    }

    QMessageBox::information(this, "Generated Password", "Generated password: " + password);

    bool save = QMessageBox::question(this, "Save Password", "Do you want to save the password?") == QMessageBox::Yes;
    if (save){
        QString savedPass = QInputDialog::getText(this, "Save Password", "What is this password for?");
        if (!savedPass.isEmpty()){
            savePassword(savedPass, password);
            QMessageBox::information(this, "Password Saved", "Password saved successfully.");
        }
    }
}

void MainWindow::chooseDiff(int &begin, int &min, int &max, bool &ok){
    QStringList difficulties = {"Easy", "Medium", "Hard"};
    QString passwordDiff = QInputDialog::getItem(this, tr("Password Difficulty"), tr("Choose difficulty:"), difficulties, 0, false, &ok);
    if(!ok || passwordDiff.isEmpty()){
        return;
    }

    if(passwordDiff == "Easy"){
        begin = 8;
        min = 6;
        max = 12;
    } else if(passwordDiff == "Medium"){
        begin = 12;
        min = 8;
        max = 18;
    } else {
        begin = 16;
        min = 12;
        max = 24;
    }
}

void MainWindow::savePassword(const QString &name, const QString &password){
    QSqlQuery query;
    query.prepare("INSERT OR REPLACE INTO passwords (name, password) VALUES (:name, :password)");
    query.bindValue(":name", name);
    query.bindValue(":password", password);

    if (!query.exec()) {
        QMessageBox::critical(this, "Database Error", query.lastError().text());
    }
}

void MainWindow::on_showButton_clicked(){
    loadPasswords();

    if (savedPasswords.empty()){
        QMessageBox::information(this, "Saved Passwords", "No saved passwords.");
        ui->passwordOutput->clear();
        return;
    }

    QString allPasswords;
    for (const auto &pair : savedPasswords){
        allPasswords += QString::fromStdString("For " + pair.first + ": " + pair.second + "\n");
    }

    ui->passwordOutput->setPlainText(allPasswords);
}

void MainWindow::on_findButton_clicked(){
    QString key = QInputDialog::getText(this, "Find Password", "Which password do you need?");
    if (key.isEmpty()) return;

    auto it = savedPasswords.find(key.toStdString());
    if (it != savedPasswords.end()){
        QMessageBox::information(this, "Password Found", "Password for " + key + ": " + QString::fromStdString(it->second));
    } else{
        QMessageBox::warning(this, "Not Found", "Password for " + key + " not found.");
    }
}

void MainWindow::on_deleteButton_clicked(){
    QString key = QInputDialog::getText(this, "Delete Password", "Which password do you want to delete?");
    if (key.isEmpty()) return;

    QSqlQuery query;
    query.prepare("DELETE FROM passwords WHERE name = :name");
    query.bindValue(":name", key);

    if (query.exec()){
        savedPasswords.erase(key.toStdString());
        QMessageBox::information(this, "Password Deleted", "Password for " + key + " has been deleted.");
    } else{
        QMessageBox::warning(this, "Not Found", "Password for " + key + " not found.");
    }
    on_showButton_clicked();
}

void MainWindow::on_addButton_clicked(){
    QString whichPassword = QInputDialog::getText(this, "Add Password", "Which password do you want to add?");
    if (whichPassword.isEmpty()) return;

    QString password = QInputDialog::getText(this, "Add Password", "Enter password:");
    if (password.isEmpty()) return;

    savePassword(whichPassword, password);
    QMessageBox::information(this, "Password Added", "Password added successfully.");
}

void MainWindow::on_clearButton_clicked(){
    ui->passwordOutput->clear();
}
