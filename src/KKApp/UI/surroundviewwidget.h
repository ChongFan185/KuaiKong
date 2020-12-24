#ifndef SURROUNDVIEWWIDGET_H
#define SURROUNDVIEWWIDGET_H
#include <QFrame>
#include <QTimer>
#include <QPainter>
#include <ctime>
#include <QTime>
#include <QDebug>

namespace KuaiKong{
    namespace UI{

    class SurroundViewWidget : public QFrame
    {
        Q_OBJECT
    public:
        SurroundViewWidget(QWidget *parent);
    };

    }
}

#endif // SURROUNDVIEWWIDGET_H
