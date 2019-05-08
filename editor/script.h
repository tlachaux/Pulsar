/*
 * Project : Pulsar 2018 - Image Processing
 */

#ifndef SCRIPT_H
#define SCRIPT_H

#include <QVector>
#include <QImage>

typedef double (*Function)(double, double);

struct Instruction
{
    int         first;
    int         second;
    int         result;
    Function    function;
};

class Script
{
public:
    Script(const QString& sources);
    QRgb execute(const QImage& image, int x, int y);

private:
    void parse(const QString& sources, int index);

    QVector<double>         mVariables;
    QVector<Instruction>    mInstructions;
};

#endif // SCRIPT_H
