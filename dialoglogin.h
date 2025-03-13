#ifndef DIALOGLOGIN_H
#define DIALOGLOGIN_H

#include <QDialog>
#include <QString>

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

private:
    Ui::DialogLogin *ui;
};

#endif // DIALOGLOGIN_H
