#include "watertank.h"
#include <QPainter>
#include <QWheelEvent>
namespace {
  constexpr int TANK_LEFT = 10;
  constexpr int TANK_TOP = 10;
  constexpr int TANK_BOTTOM = 300;
  constexpr int TANK_RIGHT = 300;
  constexpr int TANK_WIDTH = 290;
  constexpr int PEN_WIDTH = 3;
  constexpr int UPDATE_INTERVAL = 1000;
  constexpr int WATER_INCREMENT = 15;
  constexpr int NORMAL_THRESHOLD = 180;
  constexpr int WARNING_THRESHOLD = 210;
}

WaterTank::WaterTank (QWidget *parent)
    : QWidget{ parent },
      waterHeight_{DEFAULT_WATER_HEIGHT},
      timer_{new QTimer{this}} {

  setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
  this->timer_->setInterval(UPDATE_INTERVAL);

  QObject::connect(timer_, &QTimer::timeout, this, [this](){
    this->waterHeight_ += WATER_INCREMENT;
    update();

    // Emit appropriate signal based on water level
    if (this->waterHeight_ <= NORMAL_THRESHOLD) {
      emit green();
    } else if (this->waterHeight_ <= WARNING_THRESHOLD) {
      emit yellow();
    } else {
      emit red();
    }
  });
  timer_->start(UPDATE_INTERVAL);
}


QSize WaterTank::sizeHint() const {
  return QSize(400,400);
}

void WaterTank::wheelEvent(QWheelEvent *event) {
  int delta = event->angleDelta().y();

  if( delta < 0 && this->waterHeight_ > MIN_WATER_HEIGHT){
    //Scroll down to decrease the water level
    this->waterHeight_ -= WATER_HEIGHT_STEP;
    update();

           // Emit appropriate signal based on updated water level
    if (this->waterHeight_ <= NORMAL_THRESHOLD) {
      emit green();
    } else if (this->waterHeight_ <= WARNING_THRESHOLD) {
      emit yellow();
    } else {
      emit red();
    }
  }
}

void WaterTank::paintEvent(QPaintEvent *event) {
  Q_UNUSED(event);

  QPainter painter(this);

  // Set up the tools you gonna use
  QPen pen(Qt::black, PEN_WIDTH);
  painter.setPen(pen);

  // Draw the tank rectangle - no upper line bound needed, only three lines
  painter.drawLine(TANK_LEFT, TANK_TOP, TANK_LEFT, TANK_BOTTOM);     // Left
  painter.drawLine(TANK_LEFT, TANK_BOTTOM, TANK_RIGHT, TANK_BOTTOM); // Bottom
  painter.drawLine(TANK_RIGHT, TANK_BOTTOM, TANK_RIGHT, TANK_TOP);   // Right


  //Draw the water
  painter.setBrush(Qt::blue);
  painter.drawRect(TANK_LEFT, TANK_BOTTOM - this->waterHeight_, TANK_WIDTH, this->waterHeight_);
}
