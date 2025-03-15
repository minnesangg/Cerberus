#ifndef DIALOGLOGIN_H
#define DIALOGLOGIN_H

#include <QDialog>
#include <QString>
#include <QStackedWidget>
#include "headers/masterpassword.h"
#include <QMessageBox>
#include <QDebug>
#include <QFile>

namespace Ui {
class DialogLogin;
}

class DialogLogin : public QDialog
{
    Q_OBJECT

public:
    explicit DialogLogin(QWidget *parent = nullptr);
    ~DialogLogin();

private slots:
    void on_loginButton_clicked();
    void on_newMasterPassButton_clicked();

private:
    Ui::DialogLogin *ui;
    QStackedWidget *masterPassStacked;
    MasterPassword master_pass;

};

#endif // DIALOGLOGIN_H
