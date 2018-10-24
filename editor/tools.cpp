/*
 * Project : image-editor 2018
 */

#include "tools.h"

int absolute(int value)
{
    return (value < 0) ? -value : value;
}

int max(const QVector<int> &vector)
{
    int maximum = vector[0];

    for (int i=1; i < vector.size(); ++i)
    {
        if (vector[i] > maximum)
        {
            maximum = vector[i];
        }
    }

    return maximum;
}

bool in(int value, int min, int max)
{
    return (value >= min && value <= max);
}

bool isDouble(const QString& str)
{
    if (str[0] == '.' || str[str.size()] == '.')
    {
        return false;
    }

    for (int i=0; i < str.size(); ++i)
    {
        if ((str[i] < '0' || str[i] > '9') && str[i] != '.') {
            return false;
        }
    }

    return true;
}
