#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow window;
    window.resize(800, 600);
    window.setStyleSheet("QMainWindow { background-color: #2C3E50; }");
    window.setWindowTitle("Password Manager");
    window.setWindowIcon(QIcon(":/mainIcon.png"));
    window.show();

    return app.exec();
}
