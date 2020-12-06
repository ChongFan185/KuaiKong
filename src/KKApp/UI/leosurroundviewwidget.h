#ifndef LEOSURROUNDVIEWWIDGET_H
#define LEOSURROUNDVIEWWIDGET_H
#include <QFrame>
#include <QTimer>
#include <QPainter>
#include <ctime>
#include <QTime>
#include <QDebug>
#include "surroundviewwidget.h"

namespace KuaiKong{
    namespace UI{

    class LeoSurroundViewWidget : public SurroundViewWidget
    {
        Q_OBJECT
    public:
        LeoSurroundViewWidget(QWidget *parent);
    };

    }
}

#endif // LEOSURROUNDVIEWWIDGET_H
