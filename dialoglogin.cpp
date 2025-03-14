#include "dialoglogin.h"
#include "ui_dialoglogin.h"
#include "masterpassword.h"
#include <QMessageBox>
#include <QDebug>

DialogLogin::DialogLogin(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DialogLogin)
{
    ui->setupUi(this);

    this->resize(600, 400);
    this->setStyleSheet("background-color: #1e1e1e;");
    this->setWindowTitle("Cerberus");
    this->setWindowIcon(QIcon(":/mainIcon.png"));
}

DialogLogin::~DialogLogin()
{
    delete ui;
}

void DialogLogin::on_loginButton_clicked()
{
    QString password = ui->passwordLine->text();
    if(password.isEmpty()){
         QMessageBox::critical(this, "Error", "Empty password line. Please try again.");
        return;
    }
    MasterPassword master_pass;
    if (master_pass.checkMasterPass(password))
        accept();
}

