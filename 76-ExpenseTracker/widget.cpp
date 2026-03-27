#include "widget.h"
#include "./ui_widget.h"
#include "expenseproxymodel.h"
#include "QInputDialog"
#include "QMessageBox"

Widget::Widget (QWidget *parent) : QWidget (parent), ui (new Ui::Widget) {
  ui->setupUi (this);

  model = new ExpenseModel(this);

         //Set up the proxy model
  proxyModel = new ExpenseProxyModel(this);
  proxyModel->setSourceModel(model);
  proxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);


         // Set up table view
  ui->tableView->setModel(proxyModel);
  ui->tableView->resizeColumnsToContents();
  ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
  ui->tableView->setSortingEnabled(true);

         // Initialize filter column combo box
  ui->filterColumnComboBox->addItems({"All Columns", "Date", "Item", "Amount", "Category"});

  // buttons
  QObject::connect(ui->addExpenseButton, &QPushButton::clicked, this, &Widget::onAddExpenseButton);
  QObject::connect(ui->removeExpenseButton, &QPushButton::clicked, this, &Widget::onRemoveExpenseButton);


  QObject::connect(ui->filterLineEdit, &QLineEdit::textChanged, this, &Widget::onFilterLineEdit);
  QObject::connect(ui->filterColumnComboBox, &QComboBox::currentIndexChanged, this, &Widget::onFilterColumnComboBox);

}

Widget::~Widget () {
  delete ui;
}


void Widget::onAddExpenseButton() {
  bool ok;
  QString item = QInputDialog::getText(this, "Add Expense",
                                        "Item name:", QLineEdit::Normal,
                                        "Coffee", &ok);
  if (ok && !item.isEmpty()) {
    double amount = QInputDialog::getDouble(this, "Add Expense", "Amount:", 0.00, 0.00, 1000000.00, 2, &ok);
    if (ok) {
      QString category = QInputDialog::getText(this, "Add Expense", "Category:", QLineEdit::Normal, "Food", &ok);
      if (ok && !category.isEmpty()) {
        Expense *expense = new Expense(QDate::currentDate(), item, amount, category, model);
        model->addExpense(expense);
      }
    }
  }

}


void Widget::onRemoveExpenseButton() {
  QModelIndex proxyIndex = ui->tableView->currentIndex();
  if (proxyIndex.isValid()) {
    QModelIndex sourceIndex = proxyModel->mapToSource(proxyIndex);
    model->removeExpense(sourceIndex);
  } else {
    QMessageBox::warning(this, "Remove Expense", "Please select an expense to remove.");
  }

}


void Widget::onFilterLineEdit(const QString &text) {
  int column = ui->filterColumnComboBox->currentIndex() - 1; // -1 because first item is "All Columns"
  if (column == -1) {
    proxyModel->setFilterKeyColumn(-1); // Search all columns
  } else {
    proxyModel->setFilterKeyColumn(column);
  }
  proxyModel->setFilterFixedString(text);

}


void Widget::onFilterColumnComboBox(int index) {
  this->onFilterLineEdit(ui->filterLineEdit->text());
}





















