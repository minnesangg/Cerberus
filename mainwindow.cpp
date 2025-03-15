#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    databaseManager.initDatabase();
    databaseManager.loadPasswords();

    ui->listWidget->setIconSize(QSize(32, 32));

    ui->centralwidget->setStyleSheet("centralwidget { background-color: #121212; }");

    QListWidgetItem *generateItem = new QListWidgetItem("Generate Passwords");
    generateItem->setIcon(QIcon(":/generate.png"));
    ui->listWidget->addItem(generateItem);

    QListWidgetItem *manageItem = new QListWidgetItem("Manage Passwords");
    manageItem->setIcon(QIcon(":/manage.png"));
    ui->listWidget->addItem(manageItem);

    QListWidgetItem *categoriesItem = new QListWidgetItem("Categories");
    categoriesItem->setIcon(QIcon(":/categories.png"));
    ui->listWidget->addItem(categoriesItem);

    QListWidgetItem *checkItem = new QListWidgetItem("Check Password");
    checkItem->setIcon(QIcon(":/check.png"));
    ui->listWidget->addItem(checkItem);

    QListWidgetItem *settingsItem = new QListWidgetItem("Settings");
    settingsItem->setIcon(QIcon(":/settings.png"));
    ui->listWidget->addItem(settingsItem);

    ui->stackedWidget->setCurrentWidget(ui->defaultPage);

    connect(ui->listWidget, &QListWidget::currentRowChanged, this, &MainWindow::changePage);

    QFile file(":/styles.qss");
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream ts(&file);
        qApp->setStyleSheet(ts.readAll());
    }

    ui->generatedLine->setReadOnly(true);

    ui->copyBufferButton->setIcon(QIcon(":/bufferCopy.png"));
    ui->copyBufferButton->setIconSize(QSize(32, 32));
    ui->copyBufferButton->setFlat(true);
    ui->copyBufferButton->setText("");


    ui->generatedPassLayout->setAlignment(Qt::AlignCenter);
    ui->mainGenLabel->setAlignment(Qt::AlignCenter);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changePage(int index)
{
    switch (index) {
    case 0:
        ui->stackedWidget->setCurrentWidget(ui->generatePage);
        break;
    case 1:
        ui->stackedWidget->setCurrentWidget(ui->managePage);
        break;
    case 2:
        ui->stackedWidget->setCurrentWidget(ui->categoriesPage);
        break;
    case 3:
        ui->stackedWidget->setCurrentWidget(ui->checkPage);
        break;
    case 4:
        ui->stackedWidget->setCurrentWidget(ui->settingsPage);
        break;
    default:
        break;
    }
}

void MainWindow::on_generateButton_clicked()
{
    int size = ui->lengthBox->value();

    QString generated_password = password_generator.passGeneration(size);
    ui->generatedLine->setText(generated_password);

}

void MainWindow::on_deletePassButton_clicked()
{
    ui->generatedLine->clear();
    ui->passwordNameLabel->clear();
}

void MainWindow::on_copyBufferButton_clicked()
{
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(ui->generatedLine->text());

    ui->statusbar->showMessage("Saved to buffer!", 3000);
}

void MainWindow::on_savePassButton_clicked()
{
    const QString generatedPassword = ui->generatedLine->text();
    if(generatedPassword.isEmpty())
        return;

    const QString passwordName = ui->passwordNameLabel->text();
    if(passwordName.isEmpty())
        return;

    database.savePassword(passwordName, generatedPassword);
    ui->statusbar->showMessage("Password saved!", 3000);

    ui->generatedLine->clear();
    ui->passwordNameLabel->clear();
}


// void MainWindow::on_showButton_clicked() {
//     databaseManager.loadPasswords();

//     if (databaseManager.getSavedPasswords().isEmpty()) {
//         QMessageBox::information(this, "Saved Passwords", "No saved passwords.");
//         ui->passwordOutput->clear();
//         return;
//     }

//     QString allPasswords;
//     auto savedPasswords = databaseManager.getSavedPasswords();
//     for (auto it = savedPasswords.constBegin(); it != savedPasswords.constEnd(); ++it) {
//         allPasswords += "For " + it.key() + ": " + it.value() + "\n";
//     }

//     ui->passwordOutput->setPlainText(allPasswords);
// }

// void MainWindow::on_findButton_clicked() {
//     QString key = QInputDialog::getText(this, "Find Password", "Which password do you need?");
//     if (key.isEmpty()) return;

//     auto savedPasswords = databaseManager.getSavedPasswords();
//     auto it = savedPasswords.find(key);
//     if (it != savedPasswords.end()) {
//         QMessageBox::information(this, "Password Found", "Password for " + key + ": " + it.value());
//     } else {
//         QMessageBox::warning(this, "Not Found", "Password for " + key + " not found.");
//     }
// }

// void MainWindow::on_deleteButton_clicked() {
//     QString key = QInputDialog::getText(this, "Delete Password", "Which password do you want to delete?");
//     if (key.isEmpty()) return;

//     QSqlQuery query;
//     query.prepare("DELETE FROM passwords WHERE name = :name");
//     query.bindValue(":name", key);

//     if (query.exec()) {
//         if (query.numRowsAffected() > 0) {
//             QMessageBox::information(this, "Password Deleted", "Password for " + key + " has been deleted.");
//             databaseManager.getSavedPasswords().remove(key);
//         } else {
//             QMessageBox::warning(this, "Not Found", "Password for " + key + " not found.");
//         }
//     } else {
//         QMessageBox::critical(this, "Database Error", "Failed to delete password.");
//     }
//     on_showButton_clicked();
// }

// void MainWindow::on_addButton_clicked() {
//     QString whichPassword = QInputDialog::getText(this, "Add Password", "Which password do you want to add?");
//     if (whichPassword.isEmpty()) return;

//     QString password = QInputDialog::getText(this, "Add Password", "Enter password:");
//     if (password.isEmpty()) return;

//     databaseManager.savePassword(whichPassword, password);
//     QMessageBox::information(this, "Password Added", "Password added successfully.");
//     on_showButton_clicked();
// }




