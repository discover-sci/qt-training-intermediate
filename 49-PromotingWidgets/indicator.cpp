#include "indicator.h"
#include <QPainter>
#include <QPen>
#include <QBrush>

namespace {
  constexpr int UPDATE_INTERVAL = 1000;

  constexpr int LIGHT_WIDTH = 100;
  constexpr int LIGHT_HEIGHT = 100;

  constexpr int LIGHT_MARGIN = 10;
  constexpr int LIGHT_SPACING = 115;

  constexpr int FRAME_WIDTH = 120;
  constexpr int FRAME_HEIGHT = 330;

  constexpr int PEN_WIDTH = 3;

  constexpr int BLINK_INTERVAL = 300;

  constexpr int FRAME_MARGIN = 20;
}

Indicator::Indicator (QWidget *parent)
    : QWidget{ parent },
      greenActive_{false},
      redActive_{false},
      yellowActive_{false},
      lightsOn_{true},
      timer_{new QTimer(this)} {

  setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
  this->activateGreen();
  this->timer_->setInterval(BLINK_INTERVAL);

  QObject::connect(this->timer_, &QTimer::timeout, this, &Indicator::toggleLights);
  this->timer_->start(UPDATE_INTERVAL);

}

void Indicator::toggleLights() {
  this->lightsOn_ = !this->lightsOn_;
  this->update(); // redraw the widget
}

void Indicator::activateRed() {
  this->redActive_ = true;
  this->greenActive_ = this->yellowActive_ = false;
}

void Indicator::activateYellow() {
  this->yellowActive_ = true;
  this->redActive_ = this->greenActive_ = false;
}

void Indicator::activateGreen() {
  this->greenActive_ = true;
  this->yellowActive_ = this->redActive_ = false;
}


// this event gets called on update() call
void Indicator::paintEvent(QPaintEvent *event) {
  Q_UNUSED(event); // skip processing the event. It came, we do something and leave the event unused.

  // init the tools we're gonna use
  QPainter painter(this);
  QPen pen(Qt::black, PEN_WIDTH);
  painter.setPen(pen);
  painter.setBrush(Qt::gray);

  // draw the frame for all the lights
  painter.drawRect(0, 0, FRAME_WIDTH, FRAME_HEIGHT);

  const auto drawLight = [&](int yPos, bool activity, const QColor& activeColor) {
    painter.setBrush(activity && this->lightsOn_ ? activeColor : Qt::black);
    painter.drawEllipse(LIGHT_MARGIN, yPos, LIGHT_WIDTH, LIGHT_HEIGHT);
  };

  // draw the lights
  if (this->redActive_) {
    drawLight(LIGHT_MARGIN, true, Qt::red);
    drawLight(LIGHT_SPACING, false, Qt::black);
    drawLight(LIGHT_SPACING * 2 - LIGHT_MARGIN, false, Qt::black);
  } else if (this->yellowActive_) {
    drawLight(LIGHT_MARGIN, false, Qt::black);
    drawLight(LIGHT_SPACING, true, Qt::yellow);
    drawLight(LIGHT_SPACING * 2 - LIGHT_MARGIN, false, Qt::black);
  } else if (this->greenActive_) {
    drawLight(LIGHT_MARGIN, false, Qt::black);
    drawLight(LIGHT_SPACING, false, Qt::black);
    drawLight(LIGHT_SPACING * 2 - LIGHT_MARGIN, true, Qt::green);

  }


}


QSize Indicator::sizeHint() const {
  return QSize(FRAME_WIDTH, FRAME_HEIGHT + FRAME_MARGIN);



}





















