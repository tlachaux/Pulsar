/*
 * Project : image-editor 2018
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <QImage>
#include <QLabel>
#include <QWidget>

#include "toolbox.h"
#include "scriptbox.h"
#include "workshop.h"

#include "editor/editor.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Editor          mEditor;

    QWidget         *mWidget;
    QGridLayout     *mLayout;
    QProgressBar    *mProgressBar;
    Workshop        *mWorkshop;
    ToolBox         *mToolBox;
    ScriptBox       *mScriptBox;
};

#endif // MAINWINDOW_H
