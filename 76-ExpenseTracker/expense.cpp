#include "expense.h"

Expense::Expense(QObject *parent) : QObject(parent),
                                     date_(QDate::currentDate()),
                                     item_(""),
                                     amount_(0.0),
                                     category_("")
{
}

Expense::Expense(const QDate &date, const QString &item, double amount, const QString &category, QObject *parent)
    : QObject(parent),
      date_(date),
      item_(item),
      amount_(amount),
      category_(category) {
}

QDate Expense::date() const {
  return date_;
}

QString Expense::item() const {
  return item_;
}

double Expense::amount() const {
  return amount_;
}

QString Expense::category() const {
  return category_;
}

void Expense::setDate(const QDate &date) {
  if (date_ != date) {
    date_ = date;
    emit dateChanged(date_);
  }
}

void Expense::setItem(const QString &item) {
  if (item_ != item) {
    item_ = item;
    emit itemChanged(item_);
  }
}

void Expense::setAmount(double amount) {
  if (amount_ != amount) {
    amount_ = amount;
    emit amountChanged(amount_);
  }
}

void Expense::setCategory(const QString &category) {
  if (category_ != category) {
    category_ = category;
    emit categoryChanged(category_);
  }
}