#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qaesencryption.h"
#include <QMessageBox>
#include <QInputDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QRandomGenerator>
#include <QCryptographicHash>
#include <QFile>
#include <QSettings>

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



void MainWindow::masterPassword(){
    // добавить "соль"
    bool ok;
    QStringList passwords = {"Add your password", "Generate password"};
    QString masterPass = QInputDialog::getItem(this, tr("Set Master Password"), tr("Choose: "), passwords, 0, false, &ok);
    if(!ok || masterPass.isEmpty()){
        return;
    }

    QString password;
    if(masterPass == "Generate password"){
        password = passGeneration(18);
        QMessageBox::information(this, "Generated Password", "Generated password: " + password);
    } else {
        password = QInputDialog::getText(this, "Add Password", "Enter password:");
    }

    QByteArray hashedPass = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256);

    QSettings settings(QCoreApplication::applicationDirPath() + "/master_password.ini", QSettings::IniFormat);
    settings.setValue("MasterPasswordHash", QString(hashedPass.toHex()));
    QMessageBox::information(this, "Successful", "Master password set.");
}


bool MainWindow::verifyMasterPass(const QString &inputPass) {
    QByteArray inputHashed = QCryptographicHash::hash(inputPass.toUtf8(), QCryptographicHash::Sha256);   
    QByteArray savedHashed = getMasterPasswordHash();

    return inputHashed == savedHashed;
}

bool MainWindow::checkMasterPass(){
    QSettings settings(QCoreApplication::applicationDirPath() + "/master_password.ini", QSettings::IniFormat);
    if(!settings.contains("MasterPasswordHash")){
        masterPassword();
    }

    while (true) {
        bool ok;
        QString masterPass = QInputDialog::getText(this, tr("Input Master Password"), tr("Master Password:"), QLineEdit::Password, "", &ok);

        if (!ok) {
             QApplication::quit();
            return false;
        }

        if (masterPass.isEmpty() || !verifyMasterPass(masterPass)) {
            QMessageBox::critical(this, "Error", "Wrong Master Password. Please try again.");
            continue;
        }
        break;
    }
    return true;
}

QByteArray MainWindow::getMasterPasswordHash() {
    QSettings settings(QCoreApplication::applicationDirPath() + "/master_password.ini", QSettings::IniFormat);
    QString savedHashedHex = settings.value("MasterPasswordHash", "").toString();

    if(savedHashedHex.isEmpty()){
        return QByteArray();
    }
    return QByteArray::fromHex(savedHashedHex.toUtf8());
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

void MainWindow::on_generateButton_clicked(){
    int begin = 0, min = 0, max = 0;
    bool ok;

    chooseDiff(begin, min, max, ok);
    if (!ok) return;

    int passwordSize = QInputDialog::getInt(this, tr("Generate Password"), tr("Choose password size:"), begin, min, max, 1, &ok);
    if (!ok) return;

    QString password = passGeneration(passwordSize);
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

QString MainWindow::passGeneration(int passwordSize){
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

    return password;
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

void MainWindow::loadPasswords() {
    savedPasswords.clear();

    QSqlQuery query;
    query.prepare("SELECT name, password FROM passwords");

    if (!query.exec()) {
        QMessageBox::critical(this, "Database Error", query.lastError().text());
        return;
    }

    while (query.next()) {
        QString name = query.value(0).toString();
        QByteArray encryptedData = query.value(1).toByteArray();

        QByteArray iv = encryptedData.left(16);

        QByteArray encryptedPassword = encryptedData.mid(16);

        QByteArray masterKey = getMasterPasswordHash();

        QByteArray decryptedPassword;
        if (masterKey.size() == 16) {
            decryptedPassword = QAESEncryption::Decrypt(QAESEncryption::AES_128, QAESEncryption::CBC,
                                                        encryptedPassword, masterKey, iv);
        } else {
            decryptedPassword = QAESEncryption::Decrypt(QAESEncryption::AES_256, QAESEncryption::CBC,
                                                        encryptedPassword, masterKey, iv);
        }

        int endIndex = decryptedPassword.indexOf('\0');
        if (endIndex != -1) {
            decryptedPassword.truncate(endIndex);
        }

        QByteArray cleanedPassword;
        for (char c : decryptedPassword) {
            if (c >= 32 && c <= 126) {
                cleanedPassword.append(c);
            }
        }

        QString password = QString::fromUtf8(cleanedPassword);

        savedPasswords[name] = password;
    }
}

void MainWindow::savePassword(const QString &name, const QString &password) {
    QByteArray masterKey = getMasterPasswordHash();
    QByteArray IV = generateIV(16);
    QByteArray encryptedPassword;
    if(masterKey.size()== 16){
        encryptedPassword = QAESEncryption::Crypt(QAESEncryption::AES_128, QAESEncryption::CBC,
                                                  password.toUtf8(), masterKey, IV);
    } else {
        encryptedPassword = QAESEncryption::Crypt(QAESEncryption::AES_256, QAESEncryption::CBC,
                                                  password.toUtf8(), masterKey, IV);
    }

    if (encryptedPassword.isEmpty()) {
        QMessageBox::critical(this, "Encryption Error", "Failed to encrypt the password.");
        return;
    }

    QByteArray encryptedWithIV = IV + encryptedPassword;

    QSqlQuery query;
    query.prepare("INSERT OR REPLACE INTO passwords (name, password) VALUES (:name, :password)");
    query.bindValue(":name", name);
    query.bindValue(":password", encryptedWithIV);

    if (!query.exec()) {
        QMessageBox::critical(this, "Database Error", query.lastError().text());
    }
}

QByteArray MainWindow::generateIV(int size){
    QByteArray IV;
    IV.resize(size);
    for (int i = 0; i < size; ++i) {
        IV[i] = static_cast<char>(QRandomGenerator::global()->bounded(256)); // Генерация байта в диапазоне 0-255
    }

    return IV;
}

void MainWindow::on_showButton_clicked() {
    loadPasswords();

    if (savedPasswords.isEmpty()) {
        QMessageBox::information(this, "Saved Passwords", "No saved passwords.");
        ui->passwordOutput->clear();
        return;
    }

    QString allPasswords;
    for (auto it = savedPasswords.constBegin(); it != savedPasswords.constEnd(); ++it) {
        allPasswords += "For " + it.key() + ": " + it.value() + "\n";
    }

    ui->passwordOutput->setPlainText(allPasswords);
}

void MainWindow::on_findButton_clicked() {
    QString key = QInputDialog::getText(this, "Find Password", "Which password do you need?");
    if (key.isEmpty()) return;

    auto it = savedPasswords.find(key);
    if (it != savedPasswords.end()) {
        QMessageBox::information(this, "Password Found", "Password for " + key + ": " + it.value());
    } else {
        QMessageBox::warning(this, "Not Found", "Password for " + key + " not found.");
    }
}

void MainWindow::on_deleteButton_clicked() {
    QString key = QInputDialog::getText(this, "Delete Password", "Which password do you want to delete?");
    if (key.isEmpty()) return;

    QSqlQuery query;
    query.prepare("DELETE FROM passwords WHERE name = :name");
    query.bindValue(":name", key);

    if (query.exec()) {
        savedPasswords.remove(key);
        QMessageBox::information(this, "Password Deleted", "Password for " + key + " has been deleted.");
    } else {
        QMessageBox::warning(this, "Not Found", "Password for " + key + " not found.");
    }
    on_showButton_clicked();
}

void MainWindow::on_addButton_clicked() {
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
