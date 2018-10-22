/*
 * Project : image-editor 2018
 */

#include <QDesktopWidget>

#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    mWidget = new QWidget(this);

    this->setCentralWidget(mWidget);

    QSize screenSize = QDesktopWidget().availableGeometry(this).size();
    screenSize.setHeight(screenSize.height() - 80);
    screenSize.setWidth(screenSize.width() - 80);
    this->setMinimumSize(screenSize);

    mLayout         = new QGridLayout();
    mWorkshop       = new Workshop();
    mToolBox        = new ToolBox();
    mProgressBar    = new QProgressBar();

    mWorkshop->setMinimumSize(QSize(900, 900));

    mProgressBar->setMaximum(100);

    mSaveCounter = 0;

    this->displayImage();

    mLayout->addWidget(mWorkshop, 0, 0);
    mLayout->addWidget(mToolBox, 0, 1, 2, 1);
    mLayout->addWidget(mProgressBar, 1, 0, 1, 1);
    mLayout->setAlignment(mWorkshop, Qt::AlignCenter);
    mWidget->setLayout(mLayout);

    connect(mToolBox, &ToolBox::open, this, &MainWindow::loadImage);
    connect(mToolBox, &ToolBox::save, this, &MainWindow::saveImage);
    connect(mToolBox, &ToolBox::previous, this, &MainWindow::previous);
    connect(mToolBox, &ToolBox::next, this, &MainWindow::next);

    connect(mToolBox, &ToolBox::transform, this, &MainWindow::transform);

    connect(mToolBox, &ToolBox::mix, this, &MainWindow::mix);

    connect(&mEditor, &Editor::giveProgress, mProgressBar, &QProgressBar::setValue);
}

MainWindow::~MainWindow()
{

}

void MainWindow::displayImage(void)
{
    QSize imageSize = mEditor.resultSize();

    if (imageSize.width() > 1800) {
        imageSize.setWidth(1600);
    }
    if (imageSize.height() > 900) {
        imageSize.setHeight(900);
    }

    mWorkshop->setMinimumSize(imageSize);
    mWorkshop->setPixmap(QPixmap::fromImage(mEditor.result()));
}

void MainWindow::loadImage(const QString &path)
{
    mEditor.loadSource(path);
    displayImage();
}

void MainWindow::saveImage(const QString &path)
{
    mEditor.saveResult(path);
}

void MainWindow::previous(void)
{
    mEditor.previous();
    displayImage();
}

void MainWindow::next(void)
{
    mEditor.next();
    displayImage();
}

void MainWindow::transform(Filter filter)
{
    mEditor.apply(filter);
    displayImage();
}

void MainWindow::mix(const QString &path, Filter filter)
{
    mEditor.loadMixer(path);
    mEditor.apply(filter);
    displayImage();
}
