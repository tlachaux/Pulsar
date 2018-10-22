/*
 * Project : image-editor 2018
 */

#include <iostream>

#include "workshop.h"

Workshop::Workshop(QWidget* parent, Qt::WindowFlags f): QLabel(parent)
{

}

Workshop::~Workshop() {}

void Workshop::mousePressEvent(QMouseEvent* event)
{
    emit clicked(event->localPos());
}
