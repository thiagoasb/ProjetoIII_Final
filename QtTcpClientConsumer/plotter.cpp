#include "plotter.h"
#include <QPainter>
#include <QPen>
#include <QColor>
#include <QBrush>

Plotter::Plotter(QWidget *parent): QWidget(parent){
        for(int i=0; i<30; i++){
            tempos.push_back(i);
            dados.push_back(i);
        }

}

void Plotter::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QBrush brush;
    QPen pen;
    double x1, x2, y1, y2;

    painter.setRenderHint(QPainter::Antialiasing);

    brush.setColor(QColor(255,255,100));
    brush.setStyle(Qt::SolidPattern);

    painter.setBrush(brush);
    painter.setPen(pen);

    painter.drawRect(0,0,width(), height());

    pen.setColor(QColor(0,0,255));
    pen.setWidth(2);
    pen.setStyle(Qt::SolidLine);
    painter.setPen(pen);

    x1 = tempos[0]*width();
    y1 = dados[0]*(height()-dados[0]);

    for(int i=1; i<30; i++){
        x2=tempos[i]*width();
        y2=dados[i]*(height()-dados[i]);
        painter.drawLine(x1,y1,x2,y2);
        x1 = x2;
        y1 = y2;
    }

}

void Plotter::loadData(vector<double> t, vector<double> d){
    tempos=t;
    dados=d;
    repaint();
}
