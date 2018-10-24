/*
 * Project : Pulsar 2018 - Image Processing
 */

#ifndef TOOLS_H
#define TOOLS_H

#include<QVector>

int     absolute(int value);
int     max(const QVector<int> &vector);
bool    in(int value, int min, int max);
bool    isDouble(const QString& str);

#endif // TOOLS_H
