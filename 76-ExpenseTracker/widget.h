#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "expensemodel.h"
#include "expenseproxymodel.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget {
  Q_OBJECT

public:
  explicit Widget (QWidget *parent = nullptr);
  ~Widget () override;

private:
  Q_SLOT void onAddExpenseButton();
  Q_SLOT void onRemoveExpenseButton();
  Q_SLOT void onFilterLineEdit(const QString &text);
  Q_SLOT void onFilterColumnComboBox(int index);

private:
  ExpenseModel* model;
  ExpenseProxyModel* proxyModel;

private:
  Ui::Widget *ui;
};
#endif // WIDGET_H
