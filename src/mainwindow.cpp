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


#include "headers/mainwindow.h"
#include "forms/ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    startProgramm();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startProgramm() {
    QString dbFilePath = QCoreApplication::applicationDirPath() + "/passwords.db";
    database.setDatabasePath(dbFilePath);

    database.initDatabase();
    database.loadPasswords();

    ui->centralwidget->setStyleSheet("centralwidget { background-color: #121212; }");

    listWidgetSettings();
    openStyleFile();
    buttonsImages();
    allignCenter();

    ui->generatedLine->setReadOnly(true);

    ui->positiveMessageLabel->hide();
    ui->negativeMessageLabel->hide();

    setupComboBox();

    setupTable();

    QString language = settings.getLanguage();
    settings.setLanguage(language);
}

void MainWindow::listWidgetSettings() {
    ui->listWidget->setIconSize(QSize(32, 32));

    QListWidgetItem *manageItem = new QListWidgetItem(tr("Manage Passwords"));
    manageItem->setIcon(QIcon(":/manage.png"));
    ui->listWidget->addItem(manageItem);

    QListWidgetItem *generateItem = new QListWidgetItem(tr("Generate Passwords"));
    generateItem->setIcon(QIcon(":/generate.png"));
    ui->listWidget->addItem(generateItem);

    QListWidgetItem *categoriesItem = new QListWidgetItem(tr("Categories"));
    categoriesItem->setIcon(QIcon(":/categories.png"));
    ui->listWidget->addItem(categoriesItem);

    QListWidgetItem *checkItem = new QListWidgetItem(tr("Check Password"));
    checkItem->setIcon(QIcon(":/check.png"));
    ui->listWidget->addItem(checkItem);

    QListWidgetItem *backupDB = new QListWidgetItem(tr("Backups"));
    backupDB->setIcon(QIcon(":/backup.png"));
    ui->listWidget->addItem(backupDB);

    QListWidgetItem *settingsItem = new QListWidgetItem(tr("Settings"));
    settingsItem->setIcon(QIcon(":/settings.png"));
    ui->listWidget->addItem(settingsItem);

    connect(ui->listWidget, &QListWidget::currentRowChanged, this, &MainWindow::changePage);
    ui->listWidget->setAlternatingRowColors(false);
    ui->listWidget->setUniformItemSizes(true);
    ui->listWidget->setSpacing(2);

}

void MainWindow::openStyleFile() {
    QFile file(":/styles.qss");
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream ts(&file);
        qApp->setStyleSheet(ts.readAll());
    }
}

void MainWindow::buttonsImages() {
    ui->copyBufferButton->setIcon(QIcon(":/bufferCopy.png"));
    ui->copyBufferButton->setIconSize(QSize(32, 32));
    ui->copyBufferButton->setFlat(true);
    ui->copyBufferButton->setText("");

    ui->copyFindedButton->setIcon(QIcon(":/bufferCopy.png"));
    ui->copyFindedButton->setIconSize(QSize(32, 32));
    ui->copyFindedButton->setFlat(true);
    ui->copyFindedButton->setText("");

    ui->additInfoButton->setIcon(QIcon(":/addInfo.png"));
    ui->additInfoButton->setIconSize(QSize(32, 32));
    ui->additInfoButton->setFlat(true);
    ui->additInfoButton->setText("");

    ui->backupInfoButton->setIcon(QIcon(":/addInfo.png"));
    ui->backupInfoButton->setIconSize(QSize(32, 32));
    ui->backupInfoButton->setFlat(true);
    ui->backupInfoButton->setText("");

    ui->generateInfoButton->setIcon(QIcon(":/addInfo.png"));
    ui->generateInfoButton->setIconSize(QSize(32, 32));
    ui->generateInfoButton->setFlat(true);
    ui->generateInfoButton->setText("");
}

void MainWindow::allignCenter() {
    ui->generatedPassLayout->setAlignment(Qt::AlignCenter);
    ui->mainGenLabel->setAlignment(Qt::AlignCenter);
    ui->storedLabel->setAlignment(Qt::AlignCenter);
    ui->passShowLayout->setAlignment(Qt::AlignCenter);
    ui->manageLabel->setAlignment(Qt::AlignCenter);
    ui->globalLayout->setAlignment(Qt::AlignCenter);
    ui->generateLayout->setAlignment(Qt::AlignCenter);
    ui->generatedPassLayout->setAlignment(Qt::AlignCenter);
    ui->globalLayout->setAlignment(Qt::AlignCenter);
    ui->passCheckLayout->setAlignment(Qt::AlignCenter);
    ui->textTableLayout->setAlignment(Qt::AlignCenter);
    ui->backupLabelLayout->setAlignment(Qt::AlignCenter);
    ui->sendGmailLayout->setAlignment(Qt::AlignCenter);
    ui->restorePasswordLayout->setAlignment(Qt::AlignCenter);
    ui->settingsLabelLayout->setAlignment(Qt::AlignCenter);
    ui->manageLabelLayout->setAlignment(Qt::AlignCenter);
    //ui->allLanguagesLayout->setAlignment(Qt::AlignCenter);
}

void MainWindow::changePage(int index) {
    switch (index) {
    case 0:
        ui->stackedWidget->setCurrentWidget(ui->managePage);
        break;
    case 1:
        ui->stackedWidget->setCurrentWidget(ui->generatePage);
        break;
    case 2:
        ui->stackedWidget->setCurrentWidget(ui->categoriesPage);
        break;
    case 3:
        ui->stackedWidget->setCurrentWidget(ui->checkPage);
        break;
    case 4:
        ui->stackedWidget->setCurrentWidget(ui->backupPage);
        break;
    case 5:
        ui->stackedWidget->setCurrentWidget(ui->settingsPage);
        break;
    default:
        break;
    }
}

void MainWindow::setupComboBox(){
    QMap<QString, QString> langMap = {
        {"English", tr("English")},
        {"Russian", tr("Russian")},
        {"Ukrainian", tr("Ukrainian")}
    };

    ui->languageCombo->clear();

    for (auto it = langMap.begin(); it != langMap.end(); ++it) {
        ui->languageCombo->addItem(it.value());
        ui->languageCombo->setItemData(ui->languageCombo->count() - 1, it.key(), Qt::UserRole);
    }
}


void MainWindow::on_generateButton_clicked() {
    int size = ui->lengthBox->value();

    QString generated_password = password_generator.passGeneration(size);
    ui->generatedLine->setText(generated_password);

}

void MainWindow::on_deletePassButton_clicked() {
    ui->generatedLine->clear();
    ui->passwordNameLabel->clear();
}

void MainWindow::on_savePassButton_clicked() {
    const QString generatedPassword = ui->generatedLine->text();
    if(generatedPassword.isEmpty())
        return;

    const QString passwordName = ui->passwordNameLabel->text();
    if(passwordName.isEmpty()){
        ui->statusbar->showMessage(tr("Line with password's name is empty!"), 3000);
        return;
    }

    database.savePassword(passwordName, generatedPassword);
    ui->statusbar->showMessage(tr("Password saved!"), 3000);

    ui->generatedLine->clear();
    ui->passwordNameLabel->clear();
}

void MainWindow::on_findButton_clicked() {
    const QString findedName = ui->findNameLabel->text();

    if(findedName.isEmpty()){
        ui->statusbar->showMessage(tr("Line is empty!"), 3000);
        return;
    }

    auto savedPasswords = database.getSavedPasswords();
    auto findedPass = savedPasswords.find(findedName);
    if (findedPass != savedPasswords.end()) {
        ui->findedLine->setText(findedPass.value());
    } else {
        ui->findedLine->setText(tr("Password not found"));
    }

}

void MainWindow::on_deleteButton_clicked() {
    const QString findedName = ui->deleteLabel->text();
    if(findedName.isEmpty()){
        ui->statusbar->showMessage(tr("Line is empty!"), 3000);
        return;
    }

    QSqlQuery query;
    query.prepare("DELETE FROM passwords WHERE name = :name");
    query.bindValue(":name", findedName);

    if (query.exec()) {
        if (query.numRowsAffected() > 0) {
            database.deletePassword(findedName);
            ui->statusbar->showMessage(tr("Password for ") + findedName + tr(" has been deleted."), 3000);
            ui->deleteLabel->clear();
        } else {
            ui->statusbar->showMessage(tr("Password for ") + findedName + tr(" not found."), 3000);
            ui->deleteLabel->clear();
        }
    } else {
        ui->statusbar->showMessage(tr("Failed to delete password."), 3000);
        ui->deleteLabel->clear();
    }

    database.loadPasswords();
}

void MainWindow::on_addPassButton_clicked() {
    QString passwordName = ui->ownPassName->text();
    QString ownPassword = ui->ownPass->text();

    if(passwordName.isEmpty()){
        ui->statusbar->showMessage(tr("Line is empty!"), 3000);
        return;
    }
    if(ownPassword.isEmpty()){
        ui->statusbar->showMessage(tr("Line is empty!"), 3000);
        return;
    }

    database.savePassword(passwordName, ownPassword);
    ui->statusbar->showMessage(tr("Password saved!"), 3000);

    ui->ownPassName->clear();
    ui->ownPass->clear();
}

void MainWindow::on_showButton_clicked() {
    database.loadPasswords();

    auto savedPasswords = database.getSavedPasswords();
    if (savedPasswords.isEmpty()) {
        ui->statusbar->showMessage(tr("There's no passwords!"), 3000);
        return;
    }

    ui->showPassTable->clear();
    ui->showPassTable->setRowCount(savedPasswords.size());
    ui->showPassTable->setColumnCount(1);
    ui->showPassTable->setHorizontalHeaderLabels({ tr("Password's Name") });
    ui->showPassTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->showPassTable->verticalHeader()->setVisible(false);
    ui->showPassTable->setSelectionMode(QAbstractItemView::NoSelection);
    ui->showPassTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    int row = 0;
    for (auto it = savedPasswords.constBegin(); it != savedPasswords.constEnd(); ++it, ++row) {
        ui->showPassTable->setItem(row, 0, new QTableWidgetItem(it.key()));
    }
}


void MainWindow::on_showAllButton_clicked() {
    database.loadPasswords();

    auto savedPasswords = database.getSavedPasswords();
    if (savedPasswords.isEmpty()) {
        ui->statusbar->showMessage(tr("There's no passwords!"), 3000);
        return;
    }

    ui->showPassTable->clear();
    ui->showPassTable->setRowCount(savedPasswords.size());
    ui->showPassTable->setColumnCount(2);
    ui->showPassTable->setHorizontalHeaderLabels({ tr("Password's Name"), tr("Password") });
    ui->showPassTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->showPassTable->verticalHeader()->setVisible(false);
    ui->showPassTable->setSelectionMode(QAbstractItemView::NoSelection);
    ui->showPassTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    int row = 0;
    for (auto it = savedPasswords.constBegin(); it != savedPasswords.constEnd(); ++it, ++row) {
        ui->showPassTable->setItem(row, 0, new QTableWidgetItem(it.key()));
        ui->showPassTable->setItem(row, 1, new QTableWidgetItem(it.value()));
    }
}


void MainWindow::on_copyFindedButton_clicked() {
    QClipboard *clipboard = QApplication::clipboard();
    QString findedPassword = ui->findedLine->text();
    if(findedPassword != "Password not found"){
        clipboard->setText(findedPassword);
        ui->statusbar->showMessage(tr("Saved to buffer!"), 3000);
    }
}


void MainWindow::on_copyBufferButton_clicked() {
    QClipboard *clipboard = QApplication::clipboard();
    QString generatedPass = ui->generatedLine->text();
    if(!generatedPass.isEmpty()){
        clipboard->setText(generatedPass);
        ui->statusbar->showMessage(tr("Saved to buffer!"), 3000);
    }
}

void MainWindow::on_apiButton_clicked() {
    QString password = ui->checkPassLine->text();
    PwnedApiChecker *checker = new PwnedApiChecker(this);

    connect(checker, &PwnedApiChecker::passwordChecked, this, &MainWindow::onPasswordChecked);

    checker->checkPassword(password);
}

void MainWindow::onPasswordChecked(bool found, int count) {
    ui->positiveMessageLabel->clear();
    ui->negativeMessageLabel->clear();
    ui->positiveMessageLabel->hide();
    ui->negativeMessageLabel->hide();
    if(!ui->checkPassLine->text().isEmpty()){
        if (found) {
            QString breachWord = (count == 1) ? tr("breach") : tr("breaches");
            ui->negativeMessageLabel->setText(QString(tr("Your password has been found in %1 %2! Please change it!")).arg(count).arg(breachWord));
            ui->negativeMessageLabel->show();
        } else {
            ui->positiveMessageLabel->setText(tr("Your password is safe!"));
            ui->positiveMessageLabel->show();
        }
    } else {
        ui->statusbar->showMessage(tr("Line is empty!"), 3000);
    }
}

void MainWindow::on_checkAllPassButton_clicked() {
    QMap<QString, QString> passwords = database.getSavedPasswords();

    on_clearAllPassButton_clicked();

    for (const QString &password : passwords) {
        PwnedApiChecker *checker = new PwnedApiChecker(this);

        connect(checker, &PwnedApiChecker::passwordChecked, this, [this, password](bool found, int count) {
            if (found) {
                int row = ui->passwordTable->rowCount();
                ui->passwordTable->insertRow(row);
                ui->passwordTable->setItem(row, 0, new QTableWidgetItem(password));
                ui->passwordTable->setItem(row, 1, new QTableWidgetItem(QString::number(count)));
            }
            ui->passwordTable->show();
        });

        checker->checkPassword(password);
    }
}

void MainWindow::onAllPasswordChecked(bool found, int count) {
    PwnedApiChecker *checker = qobject_cast<PwnedApiChecker*>(sender());
    if (!checker || !checkerRowMap.contains(checker))
        return;
    int row = checkerRowMap[checker];

    QString breachWord = (count == 1) ? tr("breach") : tr("breaches");

    if (found) {
        ui->passwordTable->item(row, 1)->setText(QString(tr("Found in %1 %2!")).arg(count).arg(breachWord));
    } else {
        ui->passwordTable->item(row, 1)->setText(tr("Safe"));
    }

    checker->deleteLater();
}

void MainWindow::setupTable() {
    ui->passwordTable->setColumnCount(2);
    QStringList headers;
    headers << tr("Password") << tr("Breaches Count");
    ui->passwordTable->setHorizontalHeaderLabels(headers);

    ui->passwordTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->passwordTable->verticalHeader()->setVisible(false);
    ui->passwordTable->setSelectionMode(QAbstractItemView::NoSelection);
    ui->passwordTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void MainWindow::on_clearAllPassButton_clicked()
{
    ui->passwordTable->clearContents();
    ui->passwordTable->setRowCount(0);

}

void MainWindow::on_additInfoButton_clicked()
{
    QMessageBox::information(this, tr("Info"), tr("Integrated with Have I Been Pwned."));
}


void MainWindow::on_clearTableButton_clicked()
{
    ui->showPassTable->clearContents();
    ui->showPassTable->setRowCount(0);
}

void MainWindow::on_gmailSendButton_clicked()
{
    QString userGmail = ui->gmailLine->text();
    if (userGmail.isEmpty()) {
        ui->statusbar->showMessage(tr("Line is empty!"), 3000);
        return;
    }

    QString achtungString = tr("Are you sure that's YOUR email: ") + userGmail.toUpper();

    QMessageBox::StandardButton reply;
    reply = QMessageBox::warning(this, tr("ACHTUNG!"), achtungString, QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        QString password = confirmOperation();
        if (password.isEmpty()) {
            statusBar()->showMessage(tr("Password entry canceled!"), 3000);
            return;
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
            ui->gmailLine->clear();
            ui->statusbar->showMessage(tr("Backup successfully sent!"), 3000);
        } else {
            statusBar()->showMessage(tr("Incorrect password. Please try again!"), 3000);
        }
    } else {
        ui->gmailLine->clear();
        return;
    }
}

QString MainWindow::confirmOperation()
{
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

void MainWindow::on_chooseFileButton_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(
        this, tr("Choose Database"), "", tr("Databases (*.db);;All Files (*)"));

    if (!filePath.isEmpty()) {
        QString exeDir = QCoreApplication::applicationDirPath();
        QFileInfo fileInfo(filePath);
        QString destinationPath = QDir(exeDir).filePath(fileInfo.fileName());


        database.close();
        QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection);
        if (QFile::exists(destinationPath)) {
            QFile::remove(destinationPath);
        }

        if (QFile::copy(filePath, destinationPath)) {
            ui->statusbar->showMessage(tr("Database successfully added!"), 3000);
        } else {
            ui->statusbar->showMessage(tr("Error adding the database!"), 3000);
        }
    } else {
        ui->statusbar->showMessage(tr("No file selected."), 3000);
    }
    database.initDatabase();
}


void MainWindow::on_backupInfoButton_clicked()
{
    QMessageBox::information(this,tr("Info") ,tr("All passwords in the database are transmitted in an encrypted form."));
}

void MainWindow::on_generateInfoButton_clicked()
{
    QMessageBox::information(this, tr("Info"), tr("All password are creating using strong cryptographic methods."));
}

void MainWindow::on_languageButton_clicked()
{
    int index = ui->languageCombo->currentIndex();
    QString selectedLang = ui->languageCombo->itemData(index, Qt::UserRole).toString();

    if (settings.setLanguage(selectedLang)) {
        if (settings.saveLanguage(selectedLang)) {
            ui->statusbar->showMessage("New language succesfully saved!", 3000);
        } else {
            ui->statusbar->showMessage("Error saving new language.", 3000);
        }
        ui->retranslateUi(this);
        this->setWindowTitle("Cerberus");
        ui->listWidget->clear();
        listWidgetSettings();
        allignCenter();
    } else {
        ui->statusbar->showMessage(tr("Retranslating error!"), 3000);
    }
}
