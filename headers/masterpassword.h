#ifndef MASTERPASSWORD_H
#define MASTERPASSWORD_H

#include <QString>
#include <QByteArray>
#include <QSettings>
#include <QCryptographicHash>
#include <QWidget>
#include <QMessageBox>
#include <QInputDialog>
#include <QRandomGenerator>
#include <QCryptographicHash>
#include <QFile>
#include <QApplication>
#include <QSettings>
#include "headers/password_generator.h"

class MasterPassword : public QWidget{
    Q_OBJECT
public:
    MasterPassword();
    void masterPassword(QString password);
    bool verifyMasterPass(const QString &inputPass);
    bool checkMasterPass(QString password);
    QByteArray getMasterPasswordHash();
    QByteArray generateIV(int size);

private:
   PasswordGenerator password_generator;
};

#endif // MASTERPASSWORD_H
