/*
 * Project : Pulsar 2018 - Image Processing
 */

#include <math.h>

#include <QCoreApplication>
#include <QColor>

#include "editor.h"
#include "script.h"
#include "tools.h"

Editor::Editor() :
    mSource(QSize(1000, 1000), QImage::Format_RGB888),
    mResult(QSize(1000, 1000), QImage::Format_RGB888),
    mMixer(),
    mSaveCounter(0),
    mHistoryIndex(0)
{
    mSource.fill(QColor(255, 255, 255));
    mResult = mSource;
    updateHistory(mSource);
}

void Editor::loadSource(const QString &path)
{
    if (path != "")
    {
        mSource.load(path);
        mResult = mSource;
        updateHistory(mSource);
    }

    emit sRefresh(mResult);
}

void Editor::loadMixer(const QString &path, Filter filter)
{
    if (path != "")
    {
        mMixer.load(path);
        apply(filter);
    }
}

void Editor::saveResult(const QString &path)
{
    if (path != "")
    {
        QString fullPath = path + QString("/image%1.png").arg(mSaveCounter);

        if (mResult.save(fullPath))
        {
            ++mSaveCounter;
        }
    }
}

void Editor::previous(void)
{
    if (mHistoryIndex > 0)
    {
        mSource = mHistory[--mHistoryIndex];
        mResult = mSource;
    }

    emit sRefresh(mResult);
}

void Editor::next(void)
{
    if (mHistoryIndex < mHistory.size() - 1)
    {
        mSource = mHistory[++mHistoryIndex];
        mResult = mSource;
    }

    emit sRefresh(mResult);
}

void Editor::updateHistory(const QImage &image)
{
    if (mHistory.size() == 10)
    {
        mHistory.erase(mHistory.begin());
    }
    mHistoryIndex = mHistory.size();
    mHistory.push_back(image);
}

const QImage& Editor::result(void)
{
    return mResult;
}

void Editor::apply(Filter filter)
{
    QRgb rgb;

    for (int y=0; y < mSource.size().height(); ++y)
    {
        for (int x=0; x < mSource.size().width(); ++x)
        {
            switch(filter)
            {
                case Filter::Invert:
                    rgb = invert(x, y);
                    break;
                case Filter::Blur:
                    rgb = blur(x, y);
                    break;
                case Filter::Border:
                    rgb = border(x, y);
                    break;
                case Filter::Fusion:
                    rgb = fusion(x, y);
                    break;
                case Filter::Mix:
                    rgb = mix(x, y);
                    break;
                case Filter::Grey:
                    rgb = grey(x, y);
                    break;
            }
           mResult.setPixel(x, y, rgb);
        }
        float p = (((float) y) / (float) mSource.size().height()) * 100;
        emit sProgress((uint) p);

        QCoreApplication::processEvents();
    }
    updateHistory(mResult);
    mSource = mResult;

    emit sProgress(0);
    emit sRefresh(mResult);
}

void Editor::applyScript(const QString& sources)
{
    Script s = Script(sources);

}

QRgb Editor::invert(int x, int y)
{
    QRgb rgb = mSource.pixel(x, y);
    QColor color(255 - qRed(rgb), 255 - qGreen(rgb), 255 - qBlue(rgb));
    return color.rgb();
}

QRgb Editor::blur(int x, int y)
{
    int total = 1;
    int r = 0;
    int g = 0;
    int b = 0;

    QRgb rgb = mSource.pixel(x, y);

    r += qRed(rgb);
    g += qGreen(rgb);
    b += qBlue(rgb);

    for (int dy=-2; dy <= 2; ++dy)
    {
        for (int dx=-2; dx <= 2; ++dx)
        {
            int x2 = x + dx;
            int y2 = y + dy;

            if (in(x2, 0, mSource.size().width() - 1) && in(y2, 0, mSource.size().height() - 1))
            {
                rgb = mSource.pixel(x2, y2);
                r += qRed(rgb);
                g += qGreen(rgb);
                b += qBlue(rgb);
                ++total;
            }
        }
    }

    QColor color(r/total, g/total, b/total);

    return color.rgb();
}

QRgb Editor::grey(int x, int y)
{
    QRgb rgb = mSource.pixel(x, y);

    int result = (qRed(rgb) + qGreen(rgb) + qBlue(rgb))/3;
    QColor color(result, result, result);

    return color.rgb();
}

QRgb Editor::border(int x, int y)
{
    QRgb rgb1 = mSource.pixel(x, y);
    QVector<int> gaps;

    for (int dy=-1; dy <= 1; ++dy)
    {
        for (int dx=-1; dx <= 1; ++dx)
        {
            int x2 = x + dx;
            int y2 = y + dy;

            if (in(x2, 0, mSource.size().width() - 1) && in(y2, 0, mSource.size().height() - 1))
            {
                int gap = 0;
                QRgb rgb2 = mSource.pixel(x2, y2);

                gap += absolute(qRed(rgb1) - qRed(rgb2));
                gap += absolute(qGreen(rgb1) - qGreen(rgb2));
                gap += absolute(qBlue(rgb1) - qBlue(rgb2));
                gap /= 3;
                gaps.push_back(gap);
            }
        }
    }

    int result = 255 - max(gaps);
    QColor color(result, result, result);

    return color.rgb();
}

QRgb Editor::mix(int x, int y)
{
    if (x % 2 == 0 && y % 2 == 0 && x < mMixer.size().width() && y < mMixer.size().height())
    {
        return mMixer.pixel(x, y);
    }
    else
    {
        return mSource.pixel(x, y);
    }
}

QRgb Editor::fusion(int x, int y)
{
    QRgb rgb1 = mSource.pixel(x, y);

    if (x < mMixer.size().width() && y < mMixer.size().height())
    {
        QRgb rgb2 = mMixer.pixel(x, y);
        QColor color((qRed(rgb1) + qRed(rgb2))/2, (qGreen(rgb1) + qGreen(rgb2))/2, (qBlue(rgb1) + qBlue(rgb2))/2);

        return color.rgb();
    }
    else
    {
        return rgb1;
    }
}
