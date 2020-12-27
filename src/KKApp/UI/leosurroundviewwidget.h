#ifndef LEOSURROUNDVIEWWIDGET_H
#define LEOSURROUNDVIEWWIDGET_H
#include <QFrame>
#include <QTimer>
#include <QPainter>
#include <ctime>
#include <QTime>
#include <QDebug>
#include "surroundviewwidget.h"
#include "qopenglwidgettdp.h"

namespace KuaiKong{
    namespace UI{

    class LeoSurroundViewWidget : public SurroundViewWidget
    {
        Q_OBJECT
    public:
        LeoSurroundViewWidget(QWidget *parent);
    private:
        QOpenGLWidgetTdp *wndPano;
    };

    }
}

#endif // LEOSURROUNDVIEWWIDGET_H
