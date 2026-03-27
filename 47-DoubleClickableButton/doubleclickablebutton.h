#ifndef DOUBLECLICKABLEBUTTON_H
#define DOUBLECLICKABLEBUTTON_H

#include <QWidget>
#include <QPushButton>

class DoubleClickableButton : public QPushButton {
  Q_OBJECT
public:
  explicit DoubleClickableButton (QWidget *parent = nullptr);

public:
  Q_SIGNAL void doubleClickedSignal();

  // QWidget interface
protected:
  void mouseDoubleClickEvent(QMouseEvent *event) override;
};

#endif // DOUBLECLICKABLEBUTTON_H
