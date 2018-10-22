/*
 * Project : image-editor 2018
 */

#ifndef WORKSHOP_H
#define WORKSHOP_H

#include <QLabel>
#include <QWidget>
#include <QMouseEvent>

class Workshop : public QLabel
{
    Q_OBJECT

public:
    explicit Workshop(QWidget* parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());
    ~Workshop();

signals:
    void clicked(const QPointF &mouse);

protected:
    void mousePressEvent(QMouseEvent* event);

};

#endif // WORKSHOP_H
