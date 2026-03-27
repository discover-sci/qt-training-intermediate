#include "widget.h"
#include "./ui_widget.h"
#include <QPen>
#include <QDebug>
#include <QPainter>


Widget::Widget (QWidget *parent)
    : QWidget (parent),
      ui (new Ui::Widget) {
  constexpr const int MARGIN = 10;
  ui->setupUi (this);

  // Set up the pixmap
  QPixmap pixmap( this->width() - MARGIN, this->height() - MARGIN);
  pixmap.fill(Qt::gray);

  QPen pen;
  pen.setWidth(2);
  pen.setColor(Qt::white);

  const QFont font{"Consolas", 20, QFont::Bold};

  QPainter painter{&pixmap}; // painter will be painting on the pixmap, not directly on the widget
  painter.setPen(pen);
  painter.setBrush(Qt::gray);
  painter.setFont(font);

  painter.drawRect(pixmap.rect());

  painter.setBrush(Qt::blue);
  painter.drawRect(50, 50, 100, 100);
  painter.drawText(30, 120, "I'm loving Qt");


  // Apply the pixmap to the label in the ui form na dshow all thta has been drawn on a pixmap
  ui->label->setPixmap(pixmap);

}


Widget::~Widget () { delete ui; }
