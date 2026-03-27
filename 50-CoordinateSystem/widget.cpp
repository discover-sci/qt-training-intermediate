#include "widget.h"
#include "./ui_widget.h"
#include <QDebug>
#include <QPainter>

Widget::Widget (QWidget *parent) : QWidget (parent), ui (new Ui::Widget) {
  ui->setupUi (this);
}

Widget::~Widget () { delete ui; }


void Widget::paintEvent(QPaintEvent *event) {
  QPainter painter{this};

  qDebug() << "Logical coordinates:" << painter.window();
  qDebug() << "Physical coordinates:" << painter.viewport();

  // Draw a white background and set the brush back to the defaults
  painter.fillRect(rect(), Qt::white);
  painter.setBrush(Qt::NoBrush);
  painter.save();

  QPen pen(Qt::red);
  pen.setWidth(2);
  painter.setRenderHint(QPainter::Antialiasing, true);
  painter.setPen(pen);

  // This rectangle is drawn with the defaults: logical and physical coordinates are the same
  painter.drawRect(100,100,150,150);


  // Change the logical coordinates to go from (-100,-100) to (100, 100)
  painter.setWindow(-100,-100, 200, 200); // Change logical
  painter.setViewport(0,0,this->width(),this->height()); // Change physical coords


  pen.setColor(Qt::green);
  painter.setPen(pen);
  painter.drawRect(50,50,50,50);


  // Draw coordinate axes using the new logical coordinates
  painter.setPen(QPen(Qt::black, 0.5));
  painter.drawLine(-100, 0, 100, 0);  // X axis. (0,0) is the center of the widget
  painter.drawLine(0, -100, 0, 100);  // Y axis

  // Draw a rectangle in logical coordinates
  painter.setPen(QPen(Qt::darkBlue, 0.2));
  painter.drawRect(-50, -50, 100, 100); // This will be mapped to widget coordinates

  painter.restore();


  // Another example
  this->drawRectangles(painter);
}

void Widget::drawRectangles(QPainter &painter) const {

  QPen pen(Qt::red);
  pen.setWidth(3);
  painter.setPen(pen);

  qDebug() << "Logical coordinates:" << painter.window();
  qDebug() << "Physical coordinates:" << painter.viewport();

  // Draw red rectangle with default coordinates
  painter.drawRect(50, 50, 100, 100);

  // Draw green rectangle with modified logical coordinates
  painter.save();
  painter.setWindow(0, 0, 300, 200); // Change the logical coordinates.
  pen.setColor(Qt::green);
  painter.setPen(pen);
  painter.drawRect(50, 50, 100, 100);
  painter.restore();

  // Draw blue rectangle with modified physical coordinates
  painter.save();
  pen.setColor(Qt::blue);
  painter.setPen(pen);
  painter.setViewport(0, 0, 300, 200);
  painter.drawRect(50, 50, 100, 100);
  painter.restore();
}
