#include "shortradarwidget.h"

#define RADAR_WIDGET_SPAN 5
#define RADAR_WIDGET_STAGE 6
#define RADAR_WIDGET_SCALE 2
#define RADAR_WIDGET_DIVIDE 8
#define RADAR_WIDGET_BARWIDTH 80

using namespace KuaiKong::UI;

ShortRadarWidget::ShortRadarWidget(QWidget *parent):RadarWidget(parent)
{
    m_timerId=startTimer(1000);
    m_times=0;
    this->setAttribute(Qt::WA_TranslucentBackground, true);

    painter = new QPainter(this);

    picSizeX=160;
    picSizeY=400;

    sizeX=picSizeX+RADAR_WIDGET_BARWIDTH*2;
    sizeY=picSizeY+RADAR_WIDGET_BARWIDTH*2;

    base_color = new QColor(0xFF,0xF3,0xE0);
}

void ShortRadarWidget::drawBackground(){
    drawTopArc(0,0,true,true);
    drawBotArc(0,0,true,true);
    drawLeft4(0,0,true,true);
    drawRight4(0,0,true,true);
}

void ShortRadarWidget::drawSpecific(){
    update();
}

void ShortRadarWidget::paintEvent(QPaintEvent *event){
    drawBackground();
}

void ShortRadarWidget::timerEvent(QTimerEvent *event){

}

void ShortRadarWidget::drawTopArc(int col, int row, bool danger ,bool background){
    QPainter painter(this);
    QBrush brush(QColor(0xFF,0xF3,0xE0));
    painter.setPen(QPen(brush,10,Qt::SolidLine));
    for(int i=0;i<RADAR_WIDGET_STAGE;i++){
        for(int j=0;j<8;j++){
            painter.drawArc(10+(picSizeX/12*i/2)*2,10+(picSizeX/12*i/2)*2,(picSizeX-picSizeX/12*i)*2,(picSizeX-picSizeX/12*i)*2,(-37.5+30*j+RADAR_WIDGET_SPAN*2)*16,(30-RADAR_WIDGET_SPAN*(1+i*0.1))*16);
        }
    }
}

void ShortRadarWidget::drawBotArc(int col, int row, bool danger ,bool background){
    QPainter painter(this);
    QBrush brush(QColor(0xFF,0xF3,0xE0));
    painter.setPen(QPen(brush,10,Qt::SolidLine));
    for(int i=0;i<RADAR_WIDGET_STAGE;i++){
        for(int j=0;j<8;j++){
            painter.drawArc(10+(picSizeX/12*i/2)*2,10+picSizeY/3*2+(picSizeX/12*i/2)*2,(picSizeX-picSizeX/12*i)*2,(picSizeX-picSizeX/12*i)*2,(143+30*j+RADAR_WIDGET_SPAN*2)*16,(30-RADAR_WIDGET_SPAN*(1+i*0.1))*16);
        }
    }
}

void ShortRadarWidget::drawLeft4(int col, int row, bool danger, bool background){
    QPainter painter(this);
    QBrush brush(QColor(0xFF,0xF3,0xE0));
    painter.setPen(QPen(brush,10,Qt::SolidLine));
    for(int i=0;i<RADAR_WIDGET_STAGE;i++){
        for(int j=0;j<2;j++){
            QPainterPath path;
            path.moveTo((RADAR_WIDGET_SPAN*1.5+10)+RADAR_WIDGET_SPAN+RADAR_WIDGET_BARWIDTH/6*i,0+155+(picSizeY/8/2)+RADAR_WIDGET_BARWIDTH+(picSizeY/8)*j);
            path.lineTo((RADAR_WIDGET_SPAN*1.5+10)+RADAR_WIDGET_SPAN+RADAR_WIDGET_BARWIDTH/6*i,0+155+(picSizeY/8/2)+RADAR_WIDGET_BARWIDTH+(picSizeY/8)*(j+1)-RADAR_WIDGET_SPAN*3);
            painter.drawPath(path);
        }
    }
}

void ShortRadarWidget::drawRight4(int col, int row, bool danger, bool background){
    QPainter painter(this);
    QBrush brush(QColor(0xFF,0xF3,0xE0));
    painter.setPen(QPen(brush,10,Qt::SolidLine));
    for(int i=0;i<RADAR_WIDGET_STAGE;i++){
        for(int j=0;j<2;j++){
            QPainterPath path;
            path.moveTo((picSizeX+RADAR_WIDGET_BARWIDTH+10)+RADAR_WIDGET_SPAN+RADAR_WIDGET_BARWIDTH/6*i,0+155+(picSizeY/8/2)+RADAR_WIDGET_BARWIDTH+(picSizeY/8)*j);
            path.lineTo((picSizeX+RADAR_WIDGET_BARWIDTH+10)+RADAR_WIDGET_SPAN+RADAR_WIDGET_BARWIDTH/6*i,0+155+(picSizeY/8/2)+RADAR_WIDGET_BARWIDTH+(picSizeY/8)*(j+1)-RADAR_WIDGET_SPAN*3);
            painter.drawPath(path);
        }
    }
}
