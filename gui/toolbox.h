/*
 * Project : image-editor 2018
 */

#ifndef TOOLBOX_H
#define TOOLBOX_H

#include <QWidget>
#include <QPushButton>
#include <QFileDialog>
#include <QVBoxLayout>
#include <QProgressBar>
#include <QSlider>

#include "editor/editor.h"

class ToolBox : public QFrame
{
    Q_OBJECT
public:
    explicit ToolBox(QWidget *parent = nullptr);

public slots:
    void getOpenPath(void);
    void getSavePath(void);
    void getMixPath(void);
    void getFusionPath(void);

    void propagatePrevious(void);
    void propagateNext(void);
    void propagateInvert(void);
    void propagateBlur(void);
    void propagateGrey(void);
    void propagateBorder(void);

signals:
    void open(QString path);
    void save(QString path);
    void previous(void);
    void next(void);
    void transform(Filter filter);
    void mix(const QString &path, Filter filter);

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

    QFrame          *mMixFrame;
    QVBoxLayout     *mMixLayout;
    QPushButton     *mMixButton;
    QPushButton     *mFusionButton;

    QString         mDefaultPath;
};

#endif // TOOLBOX_H
