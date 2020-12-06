#ifndef RADARWIDGET_H
#define RADARWIDGET_H
#include <QFrame>
#include <QTimer>
#include <QPainter>
#include <ctime>
#include <QTime>
#include <QDebug>

namespace KuaiKong{
    namespace UI{

    class RadarWidget : public QFrame
    {
        Q_OBJECT
    public:
        RadarWidget(QWidget *parent);
        enum Direction{Top,Bottom,Left,Right};

        virtual void paintEvent(QPaintEvent *event);
        virtual void timerEvent(QTimerEvent *event);
    private:
        virtual void drawBackground();
    };

    }
}

#endif // RADARWIDGET_H
