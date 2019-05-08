/*
 * Project : Pulsar 2018 - Image Processing
 */

#include "scriptbox.h"

ScriptBox::ScriptBox(QWidget *parent) : QDialog(parent)
{
    this->setWindowTitle("Pulsar script");

    mLayout         = new QGridLayout();
    mTextEdit       = new QTextEdit();
    mCancelButton   = new QPushButton("Cancel");
    mApplyButton    = new QPushButton("Apply");

    mTextEdit->setMinimumSize(QSize(500, 500));

    mLayout->addWidget(mTextEdit, 0, 0, 1, 10);
    mLayout->addWidget(mCancelButton,1, 8, 1, 1);
    mLayout->addWidget(mApplyButton, 1, 9, 1, 1);

    this->setLayout(mLayout);

    connect(mCancelButton,  &QPushButton::clicked, this, &QDialog::close);
    connect(mApplyButton,   &QPushButton::clicked, this, &ScriptBox::apply);
}

void ScriptBox::apply(void)
{
    emit sApply(mTextEdit->toPlainText());
    this->close();
}

void ScriptBox::run(void)
{
    this->exec();
}
