#ifndef TOUCHCHARTVIEW_H
#define TOUCHCHARTVIEW_H

#include <QtCharts/QChartView>
#include <QGestureEvent>
#include <QPinchGesture>

QT_CHARTS_USE_NAMESPACE

class TouchChartView : public QChartView
{
public:
    TouchChartView(QChart *chart, QWidget *parent = nullptr)
        : QChartView(chart, parent)
    {
        setRenderHint(QPainter::Antialiasing);
        grabGesture(Qt::PinchGesture);
    }

protected:
    bool event(QEvent *event) override
    {
        if (event->type() == QEvent::Gesture)
            return gestureEvent(static_cast<QGestureEvent *>(event));
        return QChartView::event(event);
    }

private:
    bool gestureEvent(QGestureEvent *event)
    {
        if (QGesture *pinch = event->gesture(Qt::PinchGesture)) {
            return pinchTriggered(static_cast<QPinchGesture *>(pinch));
        }
        return false;
    }

    bool pinchTriggered(QPinchGesture *gesture)
    {
        if (gesture->state() == Qt::GestureUpdated) {
            qreal factor = gesture->scaleFactor();
            chart()->zoom(factor);
        }
        return true;
    }
};

#endif // TOUCHCHARTVIEW_H
