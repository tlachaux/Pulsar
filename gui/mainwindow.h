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
#include "workshop.h"

#include "editor/editor.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void displayImage(void);
    void loadImage(const QString &path);
    void saveImage(const QString &path);
    void previous(void);
    void next(void);
    void transform(Filter filter);
    void mix(const QString &path, Filter filter);

signals:
    void refreshProgress(uint progress);

private:
    uint            mSaveCounter;

    Editor          mEditor;

    QWidget         *mWidget;
    QGridLayout     *mLayout;
    QProgressBar    *mProgressBar;
    Workshop        *mWorkshop;
    ToolBox         *mToolBox;
};

#endif // MAINWINDOW_H
