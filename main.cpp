/*
 * Project : image-editor 2018
 */

#include <QApplication>

#include "gui/mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setStyleSheet("QMainWindow{background-color: lightgrey;}"
                      "QFrame{background-color: #e6e6e6;}");
    MainWindow w;
    w.show();

    return app.exec();
}
