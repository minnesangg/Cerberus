#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QByteArray>
#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QByteArray>
#include <QString>
#include <QCoreApplication>
#include <QMessageBox>
#include <QSqlError>
#include "headers/masterpassword.h"


class DatabaseManager : public QWidget  {
    Q_OBJECT
public:
    DatabaseManager();
    void initDatabase();
    void loadPasswords();
    void savePassword(const QString &name, const QString &password);
    bool deletePassword(const QString &name);
    QMap<QString, QString> getSavedPasswords() const;

private:
    QMap<QString, QString> savedPasswords;
    MasterPassword master_password;

};

#endif // DATABASE_H
