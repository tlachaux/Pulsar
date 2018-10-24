/*
 * Project : Pulsar 2018 - Image Processing
 */

#ifndef WORKSHOP_H
#define WORKSHOP_H

#include <QLabel>
#include <QWidget>
#include <QMouseEvent>
#include <QImage>

class Workshop : public QLabel
{
    Q_OBJECT

public:
    explicit Workshop(QWidget* parent = nullptr);
    ~Workshop();

public slots:
    void display(const QImage& image);

signals:
    void clicked(const QPointF &mouse);

protected:
    void mousePressEvent(QMouseEvent* event);

};

#endif // WORKSHOP_H
