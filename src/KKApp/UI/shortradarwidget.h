#ifndef SHORTRADARWIDGET_H
#define SHORTRADARWIDGET_H
#include <QFrame>
#include <QTimer>
#include <QPainter>
#include <QBrush>
#include <QColor>
#include <ctime>
#include <QTime>
#include <QDebug>
#include <QPainterPath>
#include "radarwidget.h"
#include "Data/shortradardata.h"

namespace KuaiKong{
    namespace UI{

    class ShortRadarWidget : public RadarWidget
    {
    public:
        ShortRadarWidget(QWidget *parent);
    private:
        void paintEvent(QPaintEvent *event) override;
        void timerEvent(QTimerEvent *event) override;
        void drawBackground() override;

        void drawSpecific();
        void drawBotArc(int col, int row, bool danger ,bool background);
        void drawTopArc(int col, int row, bool danger ,bool background);
        void drawLeft4(int col, int row, bool danger, bool background);
        void drawRight4(int col, int row, bool danger, bool background);

        int m_timerId;
        int m_times;
        Direction d;
        int sizeX;
        int sizeY;
        int picSizeX;
        int picSizeY;

        QPainter *painter;

        QColor *base_color;
    };

    }
}


#endif // SHORTRADARWIDGET_H
