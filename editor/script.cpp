/*
 * Project : Pulsar 2018 - Image Processing
 */

#include <QColor>

#include "script.h"
#include "tools.h"

Script::Script(const QString& sources) : mVariables(5, 0.0)
{

}

void Script::parse(const QString& sources, int index)
{
    QString word;

    while (sources[index] == ' ' && index < sources.size()) {
        ++index;
    }
    while (sources[index] != ' ' && index < sources.size()) {
        word.append(sources[index]);
        ++index;
    }

    if (isDouble(word))
    {
        mVariables.push_back(word.toDouble());
    }
    else
    {
        parse(sources, index);
    }
}

QRgb Script::execute(const QImage& image, int x, int y)
{
    QRgb rgb = image.pixel(x, y);

    mVariables[0] = qRed(rgb);
    mVariables[1] = qGreen(rgb);
    mVariables[2] = qBlue(rgb);
    mVariables[3] = x;
    mVariables[4] = y;

    for (int i=0; i < mInstructions.size(); ++i)
    {
        Instruction inst = mInstructions[i];
        mVariables[inst.result] = inst.function(mVariables[inst.first], mVariables[inst.second]);
    }

    QColor color(mVariables[0], mVariables[1], mVariables[2]);
    return color.rgb();
}
