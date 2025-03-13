#include "masterpassword.h"
#include <QMessageBox>
#include <QInputDialog>
#include <QRandomGenerator>
#include <QCryptographicHash>
#include <QFile>
#include <QApplication>
#include <QSettings>
#include "password_generator.h"

MasterPassword::MasterPassword() {}

void MasterPassword::masterPassword(){
    PasswordGenerator password_generator;
    // добавить "соль"
    bool ok;
    QStringList passwords = {"Add your password", "Generate password"};
    QString masterPass = QInputDialog::getItem(this, tr("Set Master Password"), tr("Choose: "), passwords, 0, false, &ok);
    if(!ok || masterPass.isEmpty()){
        return;
    }

    QString password;
    if(masterPass == "Generate password"){
        password = password_generator.passGeneration(18);
        QMessageBox::information(this, "Generated Password", "Generated password: " + password);
    } else {
        password = QInputDialog::getText(this, "Add Password", "Enter password:");
    }

    QByteArray hashedPass = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256);

    QSettings settings(QCoreApplication::applicationDirPath() + "/master_password.ini", QSettings::IniFormat);
    settings.setValue("MasterPasswordHash", QString(hashedPass.toHex()));
    QMessageBox::information(this, "Successful", "Master password set.");
}


bool MasterPassword::verifyMasterPass(const QString &inputPass) {
    QByteArray inputHashed = QCryptographicHash::hash(inputPass.toUtf8(), QCryptographicHash::Sha256);
    QByteArray savedHashed = getMasterPasswordHash();

    return inputHashed == savedHashed;
}

bool MasterPassword::checkMasterPass(QString password) {
    QSettings settings(QCoreApplication::applicationDirPath() + "/master_password.ini", QSettings::IniFormat);
    if(!settings.contains("MasterPasswordHash")) {
        masterPassword();
        return false;
    }

    if (!verifyMasterPass(password)) {
        QMessageBox::critical(this, "Error", "Wrong Master Password. Please try again.");
        return false;
    }

    return true;
}


QByteArray MasterPassword::getMasterPasswordHash() {
    QSettings settings(QCoreApplication::applicationDirPath() + "/master_password.ini", QSettings::IniFormat);
    QString savedHashedHex = settings.value("MasterPasswordHash", "").toString();

    if(savedHashedHex.isEmpty()){
        return QByteArray();
    }
    return QByteArray::fromHex(savedHashedHex.toUtf8());
}


QByteArray MasterPassword::generateIV(int size){
    QByteArray IV;
    IV.resize(size);
    for (int i = 0; i < size; ++i) {
        IV[i] = static_cast<char>(QRandomGenerator::global()->bounded(256)); // Генерация байта в диапазоне 0-255
    }

    return IV;
}
