/*
 * Project : Pulsar 2018 - Image Processing
 */

#include <QCoreApplication>

#include "workshop.h"

Workshop::Workshop(QWidget* parent): QLabel(parent)
{

}

Workshop::~Workshop() {}

void Workshop::mousePressEvent(QMouseEvent* event)
{
    emit clicked(event->localPos());
}

void Workshop::display(const QImage& image)
{
    QCoreApplication::processEvents();

    QSize imageSize = image.size();

    if (imageSize.width() > 1800) {
        imageSize.setWidth(1600);
    }
    if (imageSize.height() > 900) {
        imageSize.setHeight(900);
    }

    this->setMinimumSize(imageSize);
    this->setPixmap(QPixmap::fromImage(image));
}
