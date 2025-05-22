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

#include "headers/gmailsender.h"

GmailSender::GmailSender() {}

bool GmailSender::sendGmail(const QString& userGmail, QStatusBar* statusBar){
    if (userGmail.isEmpty()) {
        statusBar->showMessage(tr("Line is empty!"), 3000);
        return false;
    }

    QString achtungString = tr("Are you sure that's YOUR email: ") + userGmail.toUpper();

    QMessageBox::StandardButton reply;
    reply = QMessageBox::warning(this, tr("ACHTUNG!"), achtungString, QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        QString password = confirmOperation();
        if (password.isEmpty()) {
            statusBar->showMessage(tr("Password entry canceled!"), 3000);
            return false;
        }

        if (masterPasswordHandler.checkMasterPass(password)) {
            QString exePath;
            QString dbPath = QCoreApplication::applicationDirPath() + "/passwords.db";

#ifdef Q_OS_LINUX
            exePath = QCoreApplication::applicationDirPath() + "/send_email";
#elif defined(Q_OS_WIN)
            exePath = QCoreApplication::applicationDirPath() + "/send_email.exe";
#endif

            QStringList arguments;
            arguments << userGmail << dbPath;

            QProcess::startDetached(exePath, arguments);
            statusBar->showMessage(tr("Backup successfully sent!"), 3000);
        } else {
            statusBar->showMessage(tr("Incorrect password. Please try again!"), 3000);
            return false;
        }
    } else {
        statusBar->showMessage(tr("Operation canceled!"), 3000);
        return false;
    }
    return true;
}

QString GmailSender::confirmOperation(){
    QInputDialog dialog(this);
    dialog.setWindowTitle(tr("Confirm operation"));
    dialog.setLabelText(tr("Enter master password:"));
    dialog.setTextEchoMode(QLineEdit::Password);

    dialog.setStyleSheet(
        "QInputDialog {"
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
        );

    QString password;
    if (dialog.exec() == QDialog::Accepted) {
        password = dialog.textValue();
    }

    return password;
}
