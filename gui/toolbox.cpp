/*
 * Project : image-editor 2018
 */

#include "toolbox.h"
#include "mainwindow.h"

ToolBox::ToolBox(QWidget *parent) : QFrame(parent), mDefaultPath("/home")
{
    mLoadButton     = new QPushButton("Open image");
    mSaveButton     = new QPushButton("Save image");
    mPreviousButton = new QPushButton("<-");
    mNextButton     = new QPushButton("->");

    mInvertButton   = new QPushButton("Invert color");
    mGreyButton     = new QPushButton("Grey scale");
    mBlurButton     = new QPushButton("Blur");
    mBorderButton   = new QPushButton("Border only");
    mFusionButton   = new QPushButton("Fade fusion");
    mMixButton      = new QPushButton("Alternate fusion");

    mLayout         = new QVBoxLayout();

    mLayout->setAlignment(Qt::AlignTop);
    mLayout->setSpacing(20);

    mFileFrame      = new QFrame();
    mFileLayout     = new QGridLayout();

    mFileLayout->addWidget(mLoadButton, 0, 0, 1, 2);
    mFileLayout->addWidget(mSaveButton, 1, 0, 1, 2);
    mFileLayout->addWidget(mPreviousButton, 2, 0, 1, 1);
    mFileLayout->addWidget(mNextButton, 2, 1, 1, 1);
    mFileLayout->setAlignment(mSaveButton, Qt::AlignTop);

    mFileFrame->setLayout(mFileLayout);

    mFileFrame->setFrameStyle(6);

    mColorFrame     = new QFrame();
    mColorLayout    = new QVBoxLayout();

    mColorLayout->addWidget(mInvertButton);
    mColorLayout->addWidget(mGreyButton);

    mColorFrame->setLayout(mColorLayout);
    mColorFrame->setFrameStyle(6);

    mFilterFrame     = new QFrame();
    mFilterLayout    = new QVBoxLayout();

    mFilterLayout->addWidget(mBlurButton);
    mFilterLayout->addWidget(mBorderButton);

    mFilterFrame->setLayout(mFilterLayout);
    mFilterFrame->setFrameStyle(6);

    mMixFrame     = new QFrame();
    mMixLayout    = new QVBoxLayout();

    mMixLayout->addWidget(mFusionButton);
    mMixLayout->addWidget(mMixButton);

    mMixFrame->setLayout(mMixLayout);
    mMixFrame->setFrameStyle(6);

    mLayout->addWidget(mFileFrame);
    mLayout->addWidget(mColorFrame);
    mLayout->addWidget(mFilterFrame);
    mLayout->addWidget(mMixFrame);

    this->setLayout(mLayout);
    this->setFixedWidth(200);

    connect(mLoadButton, &QPushButton::clicked, this, &ToolBox::getOpenPath);
    connect(mSaveButton, &QPushButton::clicked, this, &ToolBox::getSavePath);
    connect(mPreviousButton, &QPushButton::clicked, this, &ToolBox::propagatePrevious);
    connect(mNextButton, &QPushButton::clicked, this, &ToolBox::propagateNext);

    connect(mInvertButton, &QPushButton::clicked, this, &ToolBox::propagateInvert);
    connect(mBlurButton, &QPushButton::clicked, this, &ToolBox::propagateBlur);
    connect(mGreyButton, &QPushButton::clicked, this, &ToolBox::propagateGrey);
    connect(mBorderButton, &QPushButton::clicked, this, &ToolBox::propagateBorder);
    connect(mFusionButton, &QPushButton::clicked, this, &ToolBox::getFusionPath);
    connect(mMixButton, &QPushButton::clicked, this, &ToolBox::getMixPath);
}

void ToolBox::getOpenPath(void)
{
    QString path = QFileDialog::getOpenFileName(this, tr("Open File"), mDefaultPath, tr("Images (*.png *.xpm *.jpg *.jpeg)"));

    if (path != "")
    {
        mDefaultPath = path;
        emit open(path);

    }
}

void ToolBox::getSavePath(void)
{
    QString path = QFileDialog::getExistingDirectory(this, tr("Open File"), mDefaultPath);

    if (path != "" && path != nullptr)
    {
        mDefaultPath = path;
        emit save(path);
    }
}

void ToolBox::propagatePrevious(void)
{
    emit previous();
}

void ToolBox::propagateNext(void)
{
    emit next();
}

void ToolBox::propagateInvert(void)
{
    emit transform(Filter::Invert);
}

void ToolBox::propagateBlur(void)
{
    emit transform(Filter::Blur);
}

void ToolBox::propagateGrey(void)
{
    emit transform(Filter::Grey);
}

void ToolBox::propagateBorder(void)
{
    emit transform(Filter::Border);
}

void ToolBox::getFusionPath(void)
{
    QString path = QFileDialog::getOpenFileName(this, tr("Open File"), mDefaultPath, tr("Images (*.png *.xpm *.jpg *.jpeg)"));

    if (path != "")
    {
        mDefaultPath = path;
        emit mix(path, Filter::Fusion);
    }
}


void ToolBox::getMixPath(void)
{
    QString path = QFileDialog::getOpenFileName(this, tr("Open File"), mDefaultPath, tr("Images (*.png *.xpm *.jpg *.jpeg)"));

    if (path != "")
    {
        mDefaultPath = path;
        emit mix(path, Filter::Mix);
    }
}
