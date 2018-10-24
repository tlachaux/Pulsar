/*
 * Project : Pulsar 2018 - Image Processing
 */

#ifndef TOOLBOX_H
#define TOOLBOX_H

#include <QWidget>
#include <QPushButton>
#include <QFileDialog>
#include <QVBoxLayout>
#include <QProgressBar>
#include <QSlider>

#include "scriptbox.h"

#include "editor/editor.h"

class ToolBox : public QFrame
{
    Q_OBJECT
public:
    explicit ToolBox(QWidget *parent = nullptr);

public slots:
    void open(void);
    void save(void);
    void previous(void);
    void next(void);

    void script(void);

    void invert(void);
    void grey(void);

    void blur(void);
    void border(void);

    void mix(void);
    void fusion(void);

signals:
    void sOpen(QString path);
    void sSave(QString path);
    void sPrevious(void);
    void sNext(void);

    void sScript(void);

    void sApply(Filter filter);
    void sMix(const QString &path, Filter filter);

private:
    QVBoxLayout     *mLayout;

    QFrame          *mFileFrame;
    QGridLayout     *mFileLayout;
    QPushButton     *mLoadButton;
    QPushButton     *mSaveButton;
    QPushButton     *mPreviousButton;
    QPushButton     *mNextButton;

    QFrame          *mColorFrame;
    QVBoxLayout     *mColorLayout;
    QPushButton     *mInvertButton;
    QPushButton     *mGreyButton;

    QFrame          *mFilterFrame;
    QVBoxLayout     *mFilterLayout;
    QPushButton     *mBlurButton;
    QPushButton     *mBorderButton;
    QPushButton     *mCustomButton;

    QFrame          *mMixFrame;
    QVBoxLayout     *mMixLayout;
    QPushButton     *mMixButton;
    QPushButton     *mFusionButton;

    QString         mDefaultPath;
};

#endif // TOOLBOX_H
