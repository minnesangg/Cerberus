#include "headers/mainwindow.h"
#include "forms/ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    databaseManager.initDatabase();
    databaseManager.loadPasswords();

    ui->listWidget->setIconSize(QSize(32, 32));
    ui->centralwidget->setStyleSheet("centralwidget { background-color: #121212; }");

    listWidgetSettings();

    QFile file(":/styles.qss");
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream ts(&file);
        qApp->setStyleSheet(ts.readAll());
    }

    ui->generatedLine->setReadOnly(true);

    copyButtonsImages();

    ui->generatedPassLayout->setAlignment(Qt::AlignCenter);
    ui->mainGenLabel->setAlignment(Qt::AlignCenter);

    MAKENAGAGREATAGAIN();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::copyButtonsImages(){
    ui->copyBufferButton->setIcon(QIcon(":/bufferCopy.png"));
    ui->copyBufferButton->setIconSize(QSize(32, 32));
    ui->copyBufferButton->setFlat(true);
    ui->copyBufferButton->setText("");

    ui->copyFindedButton->setIcon(QIcon(":/bufferCopy.png"));
    ui->copyFindedButton->setIconSize(QSize(32, 32));
    ui->copyFindedButton->setFlat(true);
    ui->copyFindedButton->setText("");

}

void MainWindow::listWidgetSettings(){
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

}

void MainWindow::MAKENAGAGREATAGAIN(){
    QVBoxLayout *layout = qobject_cast<QVBoxLayout*>(ui->settingsPage->layout());
    if (!layout) {
        layout = new QVBoxLayout(ui->settingsPage);
        ui->settingsPage->setLayout(layout);
    }


    QVideoWidget *videoWidget = new QVideoWidget(ui->settingsPage);
    QMediaPlayer *player = new QMediaPlayer(ui->settingsPage);

    videoWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    videoWidget->setMinimumSize(ui->settingsPage->size());

    player->setVideoOutput(videoWidget);
    player->setSource(QUrl::fromLocalFile("D:/Cerberus/qt/MAKENAGAGREATAGAIN.mp4"));

    player->setLoops(QMediaPlayer::Infinite);

    layout->addWidget(videoWidget);
    player->play();
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

void MainWindow::on_savePassButton_clicked()
{
    const QString generatedPassword = ui->generatedLine->text();
    if(generatedPassword.isEmpty())
        return;

    const QString passwordName = ui->passwordNameLabel->text();
    if(passwordName.isEmpty()){
        ui->statusbar->showMessage("Line with password's name is empty!", 3000);
        return;
    }

    database.savePassword(passwordName, generatedPassword);
    ui->statusbar->showMessage("Password saved!", 3000);

    ui->generatedLine->clear();
    ui->passwordNameLabel->clear();
}

void MainWindow::on_findButton_clicked()
{
    const QString findedName = ui->findNameLabel->text();

    if(findedName.isEmpty()){
        ui->statusbar->showMessage("Line is empty!", 3000);
        return;
    }

    auto savedPasswords = databaseManager.getSavedPasswords();
    auto findedPass = savedPasswords.find(findedName);
    if (findedPass != savedPasswords.end()) {
        ui->findedLine->setText(findedPass.value());
    } else {
        ui->findedLine->setText("Password not found");
    }

}

void MainWindow::on_deleteButton_clicked()
{
    const QString findedName = ui->deleteLabel->text();
    if(findedName.isEmpty()){
        ui->statusbar->showMessage("Line is empty!", 3000);
        return;
    }

    QSqlQuery query;
    query.prepare("DELETE FROM passwords WHERE name = :name");
    query.bindValue(":name", findedName);

    if (query.exec()) {
        if (query.numRowsAffected() > 0) {
            databaseManager.deletePassword(findedName);
            ui->statusbar->showMessage("Password for " + findedName + " has been deleted.", 3000);
            ui->deleteLabel->clear();
        } else {
            ui->statusbar->showMessage("Password for " + findedName + " not found.", 3000);
            ui->deleteLabel->clear();
        }
    } else {
        ui->statusbar->showMessage("Failed to delete password.", 3000);
        ui->deleteLabel->clear();
    }

    databaseManager.loadPasswords();
}

void MainWindow::on_addPassButton_clicked()
{
    QString passwordName = ui->ownPassName->text();
    QString ownPassword = ui->ownPass->text();

    if(passwordName.isEmpty()){
        ui->statusbar->showMessage("Line is empty!", 3000);
        return;
    }
    if(ownPassword.isEmpty()){
        ui->statusbar->showMessage("Line is empty!", 3000);
        return;
    }

    databaseManager.savePassword(passwordName, ownPassword);
    ui->statusbar->showMessage("Password saved!", 3000);

    ui->ownPassName->clear();
    ui->ownPass->clear();
}


void MainWindow::on_copyFindedButton_clicked()
{
    QClipboard *clipboard = QApplication::clipboard();
    QString findedPassword = ui->findedLine->text();
    if(findedPassword != "Password not found"){
        clipboard->setText(findedPassword);
        ui->statusbar->showMessage("Saved to buffer!", 3000);
    }
}


void MainWindow::on_copyBufferButton_clicked()
{
    QClipboard *clipboard = QApplication::clipboard();
    QString generatedPass = ui->generatedLine->text();
    if(!generatedPass.isEmpty()){
        clipboard->setText(generatedPass);
        ui->statusbar->showMessage("Saved to buffer!", 3000);
    }
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
// void MainWindow::on_addButton_clicked() {
//     QString whichPassword = QInputDialog::getText(this, "Add Password", "Which password do you want to add?");
//     if (whichPassword.isEmpty()) return;

//     QString password = QInputDialog::getText(this, "Add Password", "Enter password:");
//     if (password.isEmpty()) return;

//     databaseManager.savePassword(whichPassword, password);
//     QMessageBox::information(this, "Password Added", "Password added successfully.");
//     on_showButton_clicked();
// }



