#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QInputDialog>
#include <QFile>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->generateButton, &QPushButton::clicked, this, &MainWindow::on_generateButton_clicked);
    connect(ui->showButton, &QPushButton::clicked, this, &MainWindow::on_showButton_clicked);
    connect(ui->findButton, &QPushButton::clicked, this, &MainWindow::on_findButton_clicked);
    connect(ui->deleteButton, &QPushButton::clicked, this, &MainWindow::on_deleteButton_clicked);
    connect(ui->addButton, &QPushButton::clicked, this, &MainWindow::on_addButton_clicked);

    loadPasswords();
    srand(static_cast<unsigned>(time(0)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_generateButton_clicked()
{
    bool ok;
    int passwordSize = QInputDialog::getInt(this, tr("Generate Password"), tr("Choose password size:"), 8, 1, 50, 1, &ok);
    if (!ok)
        return;

    char symbols[] = {
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
        'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
        'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
        'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'
    };

    int symbolsSize = sizeof(symbols) / sizeof(symbols[0]);
    QString password;

    for (int i = 0; i < passwordSize; i++)
    {
        int randomIndex = rand() % symbolsSize;
        password += symbols[randomIndex];
    }

    QMessageBox::information(this, "Generated Password", "Generated password: " + password);

    bool save = QMessageBox::question(this, "Save Password", "Do you want to save the password?") == QMessageBox::Yes;
    if (save)
    {
        QString savedPass = QInputDialog::getText(this, "Save Password", "What is this password for?");
        if (!savedPass.isEmpty())
        {
            savedPasswords[savedPass.toStdString()] = password.toStdString();
            savePasswords();
            QMessageBox::information(this, "Password Saved", "Password saved successfully.");
        }
    }
}

void MainWindow::on_showButton_clicked()
{
    if (savedPasswords.empty())
    {
        QMessageBox::information(this, "Saved Passwords", "No saved passwords.");
        return;
    }

    QString allPasswords;
    for (const auto &pair : savedPasswords)
    {
        allPasswords += QString::fromStdString("For " + pair.first + ": " + pair.second + "\n");
    }

    ui->passwordOutput->setPlainText(allPasswords);
}

void MainWindow::on_findButton_clicked()
{
    QString key = QInputDialog::getText(this, "Find Password", "Which password do you need?");
    if (key.isEmpty())
        return;

    auto it = savedPasswords.find(key.toStdString());
    if (it != savedPasswords.end())
    {
        QMessageBox::information(this, "Password Found", "Password for " + key + ": " + QString::fromStdString(it->second));
    }
    else
    {
        QMessageBox::warning(this, "Not Found", "Password for " + key + " not found.");
    }
}

void MainWindow::on_deleteButton_clicked()
{
    QString key = QInputDialog::getText(this, "Delete Password", "Which password do you want to delete?");
    if (key.isEmpty())
        return;

    auto it = savedPasswords.find(key.toStdString());
    if (it != savedPasswords.end())
    {
        savedPasswords.erase(it);
        savePasswords();
        QMessageBox::information(this, "Password Deleted", "Password for " + key + " has been deleted.");
    }
    else
    {
        QMessageBox::warning(this, "Not Found", "Password for " + key + " not found.");
    }
}

void MainWindow::on_addButton_clicked()
{
    QString whichPassword = QInputDialog::getText(this, "Add Password", "Which password do you want to add?");
    if (whichPassword.isEmpty())
        return;

    QString password = QInputDialog::getText(this, "Add Password", "Enter password:");
    if (password.isEmpty())
        return;

    savedPasswords[whichPassword.toStdString()] = password.toStdString();
    savePasswords();
    QMessageBox::information(this, "Password Added", "Password added successfully.");
}

void MainWindow::loadPasswords()
{
    QFile file(QString::fromStdString(filename));
    if (file.open(QIODevice::ReadOnly))
    {
        QTextStream in(&file);
        while (!in.atEnd())
        {
            QString key = in.readLine();
            QString value = in.readLine();
            savedPasswords[key.toStdString()] = value.toStdString();
        }
        file.close();
    }
    else
    {
        QMessageBox::information(this, "Info", "No saved passwords found. Starting fresh.");
    }
}

void MainWindow::savePasswords()
{
    QFile file(QString::fromStdString(filename));
    if (file.open(QIODevice::WriteOnly))
    {
        QTextStream out(&file);
        for (const auto &pair : savedPasswords)
        {
            out << QString::fromStdString(pair.first) << "\n";
            out << QString::fromStdString(pair.second) << "\n";
        }
        file.close();
    }
    else
    {
        QMessageBox::critical(this, "Error", "Unable to save passwords to file.");
    }
}
