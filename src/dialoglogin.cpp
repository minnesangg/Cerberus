#include "headers/dialoglogin.h"
#include "ui_dialoglogin.h"

DialogLogin::DialogLogin(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DialogLogin)
{
    ui->setupUi(this);

    this->resize(600, 400);
    this->setStyleSheet("background-color: #1e1e1e;");
    this->setWindowTitle("Cerberus");
    this->setWindowIcon(QIcon(":/mainIcon.png"));

    masterPassStacked = ui->stackedWidget;
    QWidget *generate = ui->generate;
    QWidget *login = ui->login;

    QSettings settings(QCoreApplication::applicationDirPath() + "/master_password.ini", QSettings::IniFormat);

    if(!settings.contains("MasterPasswordHash") || !QFile::exists(QCoreApplication::applicationDirPath() + "/master_password.ini")) {
        masterPassStacked->setCurrentWidget(generate);
    } else {
        masterPassStacked->setCurrentWidget(login);
    }
}

DialogLogin::~DialogLogin()
{
    delete ui;
}

void DialogLogin::on_loginButton_clicked()
{
    QString password = ui->passwordLine->text();
    QString attemptsCounterLabel = ui->attemptsCounterLabel->text();
    int attemptsCounter = attemptsCounterLabel.toInt();

    while(attemptsCounter > 0){
        attemptsCounter--;
        if(attemptsCounter == 0){
            close();
        }

        if(password.isEmpty()){
            QMessageBox::critical(this, "Error", "Empty password line. Please try again.");
            return;
        }

        MasterPassword master_pass;
        if (master_pass.checkMasterPass(password)){
            accept();
        } else {
            ui->passwordLine->clear();

            QString attemptsLabel = QString::number(attemptsCounter);
            ui->attemptsCounterLabel->setText(attemptsLabel);
            return;
        }
    }
}

void DialogLogin::on_newMasterPassButton_clicked()
{
    QString password = ui->newMasterPassLabel->text();

    if(password.isEmpty()){
        QMessageBox::critical(this, "Error", "Empty password line. Please try again.");
        return;
    }

    master_pass.masterPassword(password);
    QMessageBox::information(this, "Success", "Master password has been set! Please log in.");

    masterPassStacked->setCurrentWidget(ui->login);
}
