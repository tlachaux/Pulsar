/*
 * Project : Pulsar 2018 - Image Processing
 */

#ifndef EDITOR_H
#define EDITOR_H

#include <math.h>

#include <QObject>
#include <QVector>
#include <QImage>


enum Filter {Invert, Blur, Grey, Border, Fusion, Mix};

class Editor : public QObject
{
    Q_OBJECT

    typedef QRgb (Editor::*Modifier)(int x, int y) const;

public:
    Editor();

public slots:
    void loadSource(const QString &path);
    void loadMixer(const QString &path, Filter filter);
    void saveResult(const QString &path);

    void previous(void);
    void next(void);

    void apply(Filter filter);
    void applyScript(const QString& sources);

    const QImage&   result(void);


private:
    void updateHistory(const QImage& image);

    Modifier selectModifier(Filter filter) const;

    QRgb invert(int x, int y)   const;
    QRgb blur(int x, int y)     const;
    QRgb grey(int x, int y)     const;
    QRgb border(int x, int y)   const;
    QRgb fusion(int x, int y)   const;
    QRgb mix(int x, int y)      const;

    QImage mSource;
    QImage mResult;
    QImage mMixer;

    QVector<QImage> mHistory;

    uint mSaveCounter;
    int  mHistoryIndex;

signals:
    void sProgress(uint progress);
    void sRefresh(const QImage& image);

};

#endif // EDITOR_H
