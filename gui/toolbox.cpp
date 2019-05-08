/*
 * Project : Pulsar 2018 - Image Processing
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
    mCustomButton   = new QPushButton("Custom filter");
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
    mFilterLayout->addWidget(mCustomButton);

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

    connect(mLoadButton,        &QPushButton::clicked, this, &ToolBox::open);
    connect(mSaveButton,        &QPushButton::clicked, this, &ToolBox::save);
    connect(mPreviousButton,    &QPushButton::clicked, this, &ToolBox::previous);
    connect(mNextButton,        &QPushButton::clicked, this, &ToolBox::next);

    connect(mCustomButton,      &QPushButton::clicked, this, &ToolBox::script);

    connect(mInvertButton,      &QPushButton::clicked, this, &ToolBox::invert);
    connect(mGreyButton,        &QPushButton::clicked, this, &ToolBox::grey);

    connect(mBlurButton,        &QPushButton::clicked, this, &ToolBox::blur);
    connect(mBorderButton,      &QPushButton::clicked, this, &ToolBox::border);

    connect(mFusionButton,      &QPushButton::clicked, this, &ToolBox::fusion);
    connect(mMixButton,         &QPushButton::clicked, this, &ToolBox::mix);
}

void ToolBox::open(void)
{
    QString path = QFileDialog::getOpenFileName(this, tr("Open File"), mDefaultPath, tr("Images (*.png *.xpm *.jpg *.jpeg)"));

    if (path != "")
    {
        mDefaultPath = path;
        emit sOpen(path);
    }
}

void ToolBox::save(void)
{
    QString path = QFileDialog::getExistingDirectory(this, tr("Open File"), mDefaultPath);

    if (path != "" && path != nullptr)
    {
        mDefaultPath = path;
        emit sSave(path);
    }
}

void ToolBox::previous(void)
{
    emit sPrevious();
}

void ToolBox::next(void)
{
    emit sNext();
}

void ToolBox::script(void)
{
    emit sScript();
}

void ToolBox::invert(void)
{
    emit sApply(Filter::Invert);
}

void ToolBox::grey(void)
{
    emit sApply(Filter::Grey);
}

void ToolBox::blur(void)
{
    emit sApply(Filter::Blur);
}

void ToolBox::border(void)
{
    emit sApply(Filter::Border);
}

void ToolBox::fusion(void)
{
    QString path = QFileDialog::getOpenFileName(this, tr("Open File"), mDefaultPath, tr("Images (*.png *.xpm *.jpg *.jpeg)"));

    if (path != "")
    {
        mDefaultPath = path;
        emit sMix(path, Filter::Fusion);
    }
}

void ToolBox::mix(void)
{
    QString path = QFileDialog::getOpenFileName(this, tr("Open File"), mDefaultPath, tr("Images (*.png *.xpm *.jpg *.jpeg)"));

    if (path != "")
    {
        mDefaultPath = path;
        emit sMix(path, Filter::Mix);
    }
}
