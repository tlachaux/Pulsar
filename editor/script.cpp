/*
 * Project : Pulsar 2018 - Image Processing
 */

#include <QColor>

#include "script.h"
#include "tools.h"

Script::Script(const QString& sources) : variables(5, 0.0)
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
        variables.push_back(word.toDouble());
    }
    else
    {
        parse(sources, index);
    }
}

QRgb Script::execute(const QImage& image, int x, int y)
{
    QRgb rgb = image.pixel(x, y);

    variables[0] = qRed(rgb);
    variables[1] = qGreen(rgb);
    variables[2] = qBlue(rgb);
    variables[3] = x;
    variables[4] = y;

    for (int i=0; i < instructions.size(); ++i)
    {
        Instruction inst = instructions[i];
        variables[inst.result] = inst.function(variables[inst.first], variables[inst.second]);
    }

    QColor color(variables[0], variables[1], variables[2]);
    return color.rgb();
}
