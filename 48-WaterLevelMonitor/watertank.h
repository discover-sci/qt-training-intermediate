#ifndef WATERTANK_H
#define WATERTANK_H

#include <QWidget>
#include <QTimer>

class WaterTank : public QWidget {
  Q_OBJECT
public:
  explicit WaterTank (QWidget *parent = nullptr);

public:
  Q_SIGNAL void red();    // Emitted when water level is critical
  Q_SIGNAL void yellow(); // Emitted when water level is high
  Q_SIGNAL void green();  // Emitted when water level is normal

private:
  static constexpr int DEFAULT_WATER_HEIGHT = 50;
  static constexpr int MIN_WATER_HEIGHT = 10;
  static constexpr int WATER_HEIGHT_STEP = 10;

  int waterHeight_{DEFAULT_WATER_HEIGHT}; ///< Current water height in pixels
  QTimer* timer_{nullptr};


  // QWidget interface
public:
  QSize sizeHint() const override;

protected:
  void wheelEvent(QWheelEvent *event) override;
  void paintEvent(QPaintEvent *event) override;
};

#endif // WATERTANK_H
