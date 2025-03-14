#ifndef MASTERPASSWORD_H
#define MASTERPASSWORD_H

#include <QString>
#include <QByteArray>
#include <QSettings>
#include <QCryptographicHash>
#include <QWidget>

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

};

#endif // MASTERPASSWORD_H
