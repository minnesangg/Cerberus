#include "headers/masterpassword.h"


MasterPassword::MasterPassword() {}

void MasterPassword::masterPassword(QString password){
    // добавить "соль"
    password = password.trimmed();
    QByteArray hashedPass = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256);

    QSettings settings(QCoreApplication::applicationDirPath() + "/master_password.ini", QSettings::IniFormat);
    settings.setValue("MasterPasswordHash", QString(hashedPass.toHex()));
}


bool MasterPassword::verifyMasterPass(const QString &inputPass) {
    QByteArray inputHashed = QCryptographicHash::hash(inputPass.toUtf8(), QCryptographicHash::Sha256);
    QByteArray savedHashed = getMasterPasswordHash();

    return inputHashed == savedHashed;
}

bool MasterPassword::checkMasterPass(QString password) {
    QSettings settings(QCoreApplication::applicationDirPath() + "/master_password.ini", QSettings::IniFormat);

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
        IV[i] = static_cast<char>(QRandomGenerator::global()->bounded(256));
    }

    return IV;
}
