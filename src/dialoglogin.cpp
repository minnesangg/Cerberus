/*
 * Cerberus - Password Manager
 * Copyright (C) 2025 minnesang
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 */


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

    QString attempts = settingsHandler.getAttempts();
    ui->attemptsCounterLabel->setText(attempts);

    updateStyles();
}

DialogLogin::~DialogLogin() {
    delete ui;
}

void DialogLogin::updateStyles(){
    QString darkStyle =  "QInputDialog {"
        "    color: #2ECC71;"
        "    border: 2px solid #2ECC71;"
        "}"
        "QLabel {"
        "    color: #2ECC71;"
        "}"
        "QLineEdit {"
        "    background-color: #1E1E1E;"
        "    color: #2ECC71;"
        "    border: 2px solid #2ECC71;"
        "    border-radius: 5px;"
        "    padding: 5px;"
        "}"
        "QPushButton {"
        "    background-color: #2ECC71;"
        "    color: #121212;"
        "    border-radius: 5px;"
        "    padding: 5px 10px;"
        "}"
        "QPushButton:hover {"
        "    background-color: #27AE60;"
        "}"
        "QPushButton:pressed {"
        "    background-color: #1E7C49;"
        "}"
        "QDialogButtonBox QPushButton {"
        "    background-color: #2ECC71;"
        "    color: #121212;"
        "    border-radius: 5px;"
        "    padding: 5px 10px;"
        "}"
        "QDialogButtonBox QPushButton:hover {"
        "    background-color: #27AE60;"
        "}"
        "QDialogButtonBox QPushButton:pressed {"
        "    background-color: #1E7C49;"
        "}";
    qApp->setStyleSheet(darkStyle);
}

void DialogLogin::on_loginButton_clicked() {
    QString password = ui->passwordLine->text();
    QString attemptsCounterLabel = ui->attemptsCounterLabel->text();
    int attemptsCounter = attemptsCounterLabel.toInt();

    while(attemptsCounter > 0){
        attemptsCounter--;
        if(attemptsCounter == 0){
            close();
        }

        const QString style = getStyle();
        if(password.isEmpty()){
            QMessageBox box(this);
            box.setIcon(QMessageBox::Critical);
            box.setText(tr("Empty password line. Please try again."));
            box.setWindowTitle(tr("Error"));
            box.setStyleSheet(style);
            box.exec();

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

QString DialogLogin::getStyle() const{
    QString style =             "QLabel {"
        "    color: #2ECC71;"
        "}"
        "QPushButton {"
        "    background-color: #2ECC71;"
        "    color: #121212;"
        "    border-radius: 5px;"
        "    padding: 5px 10px;"
        "}"
        "QPushButton:hover {"
        "    background-color: #27AE60;"
        "}"
        "QPushButton:pressed {"
        "    background-color: #1E7C49;"
        "}"
        "QMessageBox {"
        "    background-color: #1E1E1E;"
        "}";

    return style;
}

void DialogLogin::on_newMasterPassButton_clicked() {

    const QString style = getStyle();

    QString password = ui->newMasterPassLabel->text();
    QString repeatedPassword = ui->repeatPassLabel->text();

    if(password.isEmpty() || repeatedPassword.isEmpty()){
        QMessageBox box(this);
        box.setIcon(QMessageBox::Critical);
        box.setText(tr("Password line is empty. Try again."));
        box.setWindowTitle(tr("Error"));
        box.setStyleSheet(style);
        box.exec();

        return;
    }

    if(password == repeatedPassword){
        master_pass.masterPassword(password);
        QMessageBox box(this);
        box.setIcon(QMessageBox::Information);
        box.setText(tr("Master password has been set! Please log in."));
        box.setWindowTitle(tr("Success"));
        box.setStyleSheet(style);
        box.exec();

        masterPassStacked->setCurrentWidget(ui->login);
    } else {
        QMessageBox box(this);
        box.setIcon(QMessageBox::Critical);
        box.setText(tr("The repeated password does not match the original password."));
        box.setWindowTitle(tr("Warning"));
        box.setStyleSheet(style);
        box.exec();

        ui->newMasterPassLabel->clear();
        ui->repeatPassLabel->clear();
    }

}

