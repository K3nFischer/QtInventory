#include "mainwindow.h"
#include <iostream>
#include <QApplication>

int main(int argc, char *argv[]) {
    std::cout << "hello" << std::endl;
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
