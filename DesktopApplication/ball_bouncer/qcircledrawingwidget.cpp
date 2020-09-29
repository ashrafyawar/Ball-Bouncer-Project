#include "qcircledrawingwidget.h"

#include <iostream>

QCircleDrawingWidget::QCircleDrawingWidget(QWidget *parent) : QWidget(parent)
{
}

QCircleDrawingWidget::~QCircleDrawingWidget()
{
}

void QCircleDrawingWidget::setDrawData(int pos_x, int pos_y, float radius)
{
    this->pos_x = pos_x;
    this->pos_y = pos_y;
    this->radius = radius;
    repaint();
}

void QCircleDrawingWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    QRadialGradient radialGrad(QPointF(this->pos_x + this->radius / 5, this->pos_y - this->radius / 5), this->radius);
    radialGrad.setColorAt(0, { 255, 175, 103 } );
    radialGrad.setColorAt(1, { 255, 85, 0 } );
    this->circle_brush = QBrush(radialGrad);

    painter.setBrush(circle_brush);
    painter.drawEllipse(QPointF(this->pos_x, this->pos_y), this->radius, this->radius);
}
