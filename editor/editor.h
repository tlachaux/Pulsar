/*
 * Project : image-editor 2018
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

public:
    Editor();

    void apply(Filter filter);

    void loadSource(const QString &path);
    void loadMixer(const QString &path);
    void saveResult(const QString &path);

    void previous(void);
    void next(void);
    void updateHistory(const QImage& image);

    const QImage&   result(void);
    QSize           resultSize(void);

    QRgb invert(int x, int y);
    QRgb blur(int x, int y);
    QRgb grey(int x, int y);
    QRgb border(int x, int y);
    QRgb fusion(int x, int y);
    QRgb mix(int x, int y);

private:
    QImage mSource;
    QImage mResult;
    QImage mMixer;

    QVector<QImage> mHistory;

    uint mSaveCounter;
    int mHistoryIndex;

signals:
    void giveProgress(uint p);

};

#endif // EDITOR_H
