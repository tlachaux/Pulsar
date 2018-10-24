/*
 * Project : Pulsar 2018 - Image Processing
 */

#include <QApplication>

#include "gui/mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setStyleSheet("QMainWindow  {background-color: lightgrey;}"
                      "QFrame       {background-color: #e6e6e6;}"
                      "QTextEdit    {background-color: white;}");
    MainWindow w;
    w.show();

    return app.exec();
}
