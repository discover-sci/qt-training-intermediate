#ifndef EXPENSE_H
#define EXPENSE_H

#include <QObject>
#include <QDate>

class Expense : public QObject {
  Q_OBJECT
public:
  explicit Expense(QObject *parent = nullptr);
  explicit Expense(const QDate &date, const QString &item, double amount, const QString &category, QObject *parent = nullptr);

  QDate date() const;
  QString item() const;
  double amount() const;
  QString category() const;

  void setDate(const QDate &date);
  void setItem(const QString &item);
  void setAmount(double amount);
  void setCategory(const QString &category);

signals:
  void dateChanged(const QDate &date);
  void itemChanged(const QString &item);
  void amountChanged(double amount);
  void categoryChanged(const QString &category);

private:
  QDate date_;
  QString item_;
  double amount_;
  QString category_;

signals:
};

#endif // EXPENSE_H
