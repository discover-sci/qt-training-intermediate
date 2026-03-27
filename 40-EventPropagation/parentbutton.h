#ifndef PARENTBUTTON_H
#define PARENTBUTTON_H

#include <QObject>
#include <QWidget>
#include <QPushButton>

class ParentButton : public QPushButton {
  Q_OBJECT
public:
  explicit ParentButton (QWidget *parent = nullptr);

signals:

  // QWidget interface
protected:
  void mousePressEvent(QMouseEvent *event) override;
};

#endif // PARENTBUTTON_H
