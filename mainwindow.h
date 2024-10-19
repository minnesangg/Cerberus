#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <unordered_map>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_generateButton_clicked();
    void on_showButton_clicked();
    void on_findButton_clicked();
    void on_deleteButton_clicked();
    void on_addButton_clicked();

    void on_clearButton_clicked();

private:
    Ui::MainWindow *ui;
    std::unordered_map<std::string, std::string> savedPasswords;
    const std::string filename = "password.txt";

    void loadPasswords();
    void savePasswords();
};

#endif // MAINWINDOW_H
