#include <QApplication>
#include "mainwindow.h"
#include "dialoglogin.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    DialogLogin login;
    if (login.exec() == QDialog::Accepted) {
        MainWindow window;
        window.resize(1000, 700);
        window.setStyleSheet("QMainWindow { background-color: #2C2C2C; }");
        window.setWindowTitle("Cerberus");
        window.setWindowIcon(QIcon(":/mainIcon.png"));
        window.show();

        return app.exec();
    }

    return 0;
}
