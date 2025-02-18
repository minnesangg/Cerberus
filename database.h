#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QByteArray>
#include <QWidget>

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
};

#endif // DATABASE_H
