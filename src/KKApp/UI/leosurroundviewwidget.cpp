#include "leosurroundviewwidget.h"
using namespace KuaiKong::UI;

LeoSurroundViewWidget::LeoSurroundViewWidget(QWidget *parent):SurroundViewWidget(parent)
{
    int diswidth = 700;
    int disheight = 720;
    wndPano = new QOpenGLWidgetTdp(this);
    wndPano->setGeometry(QRect(QPoint(0, 0), QSize(diswidth, disheight)));

    QPalette pal(wndPano->palette());
    pal.setColor(QPalette::Background, Qt::black);
    wndPano->setAutoFillBackground(true);
    wndPano->setPalette(pal);
    wndPano->show();

    FILE *strfp = fopen("./rtspinfo", "r");
    if(strfp != NULL){
         char line[1024];
         int linecnt = 0;
         int ccnt=0;
         while(!feof(strfp)){
             fgets(line, 1000, strfp);
             if(strlen(line) > 1){
                 //printf("[%d]:%s",linecnt, line);
                 linecnt++;
             }

             printf("=%d=%d [%d]=%s", ccnt++, strlen(line), linecnt-1,  line);
             if(linecnt==4){//
                 break;
             }
         }
         fclose(strfp);
     }

    strfp = fopen("./rtspinfo", "r");
    if(strfp != NULL){
        char line[1024];
        int linecnt = 0;
        while(!feof(strfp)){
            fgets(line, 1000, strfp);
            if(strlen(line) > 1){
                printf("[%d]:%s",linecnt, line);

                wndPano->setSourceRtsp(linecnt, line);
                linecnt++;
            }
            if(linecnt==4){//
                break;
            }
        }
        fclose(strfp);
    }
    wndPano->show();
}
