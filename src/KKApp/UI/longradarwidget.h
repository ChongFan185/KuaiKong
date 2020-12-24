#ifndef LONGRADARWIDGET_H
#define LONGRADARWIDGET_H
#include <QFrame>
#include <QTimer>
#include <QPainter>
#include <ctime>
#include <QTime>
#include <QDebug>
#include "radarwidget.h"

namespace KuaiKong{
    namespace UI{

    class LongRadarWidget : public RadarWidget
    {
        Q_OBJECT
    public:
        LongRadarWidget(QWidget *parent);
    };

    }
}

#endif // LONGRADARWIDGET_H
