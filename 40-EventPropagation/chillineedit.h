#ifndef CHILLINEEDIT_H
#define CHILLINEEDIT_H

#include <QObject>
#include <QWidget>
#include "parentlineedit.h"


class ChilLineEdit : public ParentLineEdit {
  Q_OBJECT
public:
  explicit ChilLineEdit (QWidget *parent = nullptr);

signals:

  // QWidget interface
protected:
  void keyPressEvent(QKeyEvent *event) override;
};

#endif // CHILLINEEDIT_H
