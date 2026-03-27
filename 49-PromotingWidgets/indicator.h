#ifndef INDICATOR_H
#define INDICATOR_H

#include <QWidget>
#include <QTimer>

class Indicator : public QWidget {
  Q_OBJECT
public:
  explicit Indicator (QWidget *parent = nullptr);

  Q_SLOT void toggleLights();
public:
  Q_SLOT void activateRed();
  Q_SLOT void activateYellow();
  Q_SLOT void activateGreen();

private:
  bool redActive_{false};
  bool yellowActive_{false};
  bool greenActive_{false};
  bool lightsOn_{true};
  QTimer* timer_{nullptr};

  // QWidget interface
protected:
  void paintEvent(QPaintEvent *event) override;

  // QWidget interface
public:
  QSize sizeHint() const override;
};

#endif // INDICATOR_H
