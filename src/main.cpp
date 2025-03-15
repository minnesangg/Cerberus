#include <QApplication>
#include "headers/mainwindow.h"
#include "headers/dialoglogin.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    DialogLogin login;
    if (login.exec() == QDialog::Accepted) {
        MainWindow window;
        window.resize(1000, 700);
        window.setStyleSheet("QMainWindow { background-color: #121212; }");
        window.setWindowTitle("Cerberus");
        window.setWindowIcon(QIcon("D:/Cerberus/qt/Cerberus/resources/mainIcon.png"));
        window.show();

        return app.exec();
    }

    return 0;
}
