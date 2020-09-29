#ifndef QCIRCLEDRAWINGWIDGET_H
#define QCIRCLEDRAWINGWIDGET_H

#include <QWidget>
#include <QPainter>

class QCircleDrawingWidget : public QWidget
{
    Q_OBJECT
public:
    explicit QCircleDrawingWidget(QWidget *parent = nullptr);
    ~QCircleDrawingWidget();

    void setDrawData(int pos_x, int pos_y, float radius);

signals:


protected:
    void paintEvent(QPaintEvent *) override;

private:
    QBrush circle_brush;

private:
    int pos_x;
    int pos_y;
    float radius;
};

#endif // QCIRCLEDRAWINGWIDGET_H
