#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QKeyEvent>
#include <math.h>
#include <iostream>
#include "signal.h"

float a;
float b;
float c;
double cX;
double cY;
int keyPressed;
double scaleArray[]{};
QPoint mousePoint = QPoint(1,1);
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    mousePoint = QPoint(this->width(),this->height());
    setMouseTracking(true);
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
   this->setMouseTracking(true);
   mousePoint = event->pos();
   cX =  mousePoint.x()/ ((double)this->width());
   cY =  mousePoint.y() / ((double)this->height());

   //ui->label->setText(QString::number(cX));
   //ui->label_2->setText(QString::number((double)this->width() / 2));
   //ui->label_3->setText(QString::number(mousePoint.x()));

   update();
}

void MainWindow::wheelEvent(QWheelEvent* event)
{
    if(event->delta() > 0 && keyPressed == Qt::Key_Shift)
    {
          a += 1 - cX;
          //b += 1 - cY;
          //c -= cX ;
    }
    else if(event->delta() < 0 && keyPressed == Qt::Key_Shift)
    {
          a -= 1 - cX;
         //b -= 1 - cY;
          //c += cX;
    }

    else if(event->delta() > 0 && keyPressed == Qt::Key_Control)
    {
        c += cX;
    }

    else if(event->delta() < 0 && keyPressed == Qt::Key_Control)
    {
        c -= cX;
    }

    else if(event->delta() > 0)
    {
         //c -= cX ;
         b += 1 + cY;
    }
    else if(event->delta() < 0 )
    {
        //c += cX ;
        b -= 1 - cY;
    }

    this->update();
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    keyPressed = event->key();
    this->update();
}

void MainWindow::keyReleaseEvent(QKeyEvent* event)
{
    keyPressed = Qt::Key_unknown;
    this->update();
}

void MainWindow::graph()
{
    auto sig = new Signal(500);
        sig->generate_sine(100.0, 2.0);
        auto scaleArray = sig->values;
    if (a == 0)
        a = this->width() / sig->signal_size;
    if (b == 0)
        b = 120;


    QPainter painter(this);
    painter.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::FlatCap));

    painter.drawLine(50 + c * 5,this->height() - 50,50 + c * 5,50);
    painter.drawLine(50 + c * 5,this->height() / 2,this->width()- 50,this->height()  /2);

    for(int i = 50; i < this->width(); i += a)
    {
        if(a < 3)
        {
            a = 3;
        }

        if (i < this->width() - 50)
        {
            auto y1 = this->height() / 2 + 5 ;
            auto y2 = this->height() / 2 - 5 ;
            if (i > 50){
              painter.drawLine(i + c * 5, y1, i + c * 5, y2);
            }

        }
    }

    for(int i = this->height() / 2 - b; i > 50; i -= b )
    {
        auto jopa = i ;
        painter.drawLine(45 + c * 5,jopa,55 +c * 5,jopa);
    }
    for(int i = this->height() / 2 + b; i < this->height(); i += b )
    {
       auto jopa = i ;
       painter.drawLine(45 + c * 5 ,jopa ,55 + c * 5,jopa);
    }

    for(int i = 0; i < sig->signal_size - 1; i++)
    {
        auto eWidth = 8;

        painter.setPen(QPen(Qt::green, 1, Qt::SolidLine, Qt::FlatCap));
        painter.drawLine(50 + i * a + c * 5,this->height() / 2 - scaleArray[i] * b,50 + (i + 1) * a + c * 5,this->height() / 2 - scaleArray[i+1] * b);

        painter.setPen(QPen(Qt::red, 1, Qt::SolidLine, Qt::FlatCap));
        painter.drawEllipse(50 + i * a + c * 5 - eWidth/2,this->height() / 2 - scaleArray[i] * b   - eWidth/2,eWidth,eWidth);
    }

    for(int i = 0; i < sig->signal_size - 1; i+= 5)
    {
        auto eWidth = 8;

            painter.setPen(QPen(Qt::gray, 1, Qt::DotLine, Qt::FlatCap));
            painter.drawLine(50 + i * a + c * 5,this->height() / 2 - scaleArray[i] * b,50 + i * a + c * 5,this->height() / 2);

            painter.setPen(QPen(Qt::darkMagenta, 1, Qt::SolidLine, Qt::FlatCap));
            if(i != 0) painter.drawText(50 + i * a + c * 5,this->height() / 2 +50,QString::number(i));

        if(b > 5)
        {
            //painter.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::FlatCap));
            //painter.drawText(35,this->height() / 2 - scaleArray[i] * b,QString::number(scaleArray[i]));

            //painter.setPen(QPen(Qt::gray, 1, Qt::DotLine, Qt::FlatCap));
            //painter.drawLine(50 + i * a + c * 5,this->height() / 2 - scaleArray[i] * b,35,this->height() / 2 - scaleArray[i] * b);
        }
    }
    painter.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::FlatCap));
    painter.drawEllipse(mousePoint,2,2);
}

void MainWindow::paintEvent(QPaintEvent*) {
    graph();
}

