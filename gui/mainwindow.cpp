/*
 * Project : image-editor 2018
 */

#include <QDesktopWidget>

#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setWindowTitle("Pulsar");
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

    mWorkshop->display(mEditor.result());
    mProgressBar->setMaximum(100);

    mLayout->addWidget(mWorkshop, 0, 0, 1, 1);
    mLayout->addWidget(mToolBox, 0, 1, 2, 1);
    mLayout->addWidget(mProgressBar, 1, 0, 1, 1);
    mLayout->setAlignment(mWorkshop, Qt::AlignCenter);
    mWidget->setLayout(mLayout);

    mScriptBox = new ScriptBox(this);

    connect(mToolBox, &ToolBox::sOpen,      &mEditor,       &Editor::loadSource);
    connect(mToolBox, &ToolBox::sSave,      &mEditor,       &Editor::saveResult);
    connect(mToolBox, &ToolBox::sPrevious,  &mEditor,       &Editor::previous);
    connect(mToolBox, &ToolBox::sNext,      &mEditor,       &Editor::next);
    connect(mToolBox, &ToolBox::sApply,     &mEditor,       &Editor::apply);
    connect(mToolBox, &ToolBox::sMix,       &mEditor,       &Editor::loadMixer);

    connect(mToolBox,   &ToolBox::sScript,  mScriptBox,     &ScriptBox::run);
    connect(mScriptBox, &ScriptBox::sApply, &mEditor,       &Editor::applyScript);

    connect(&mEditor, &Editor::sRefresh,    mWorkshop,      &Workshop::display);
    connect(&mEditor, &Editor::sProgress,   mProgressBar,   &QProgressBar::setValue);
}

MainWindow::~MainWindow()
{

}
