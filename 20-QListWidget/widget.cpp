#include "widget.h"
#include "./ui_widget.h"
#include "QStringList"

Widget::Widget (QWidget *parent) : QWidget (parent), ui (new Ui::Widget) {
  ui->setupUi (this);

  // ui->listWidget->addItem("Item1");
  // ui->listWidget->addItem("Item2");
  // ui->listWidget->addItem("Item3");
  auto items = std::vector<std::string>{"item0", "item1", "item2", "item3", "item4", "item5", "item6", "item7", "item8", "item9"};

  // use QStringList for UI, not std::vector
  QStringList list;
  list.reserve(static_cast<int>(items.size()));
  for (const auto &s : items)
    list.append(QString::fromStdString(s));
  ui->listWidget->addItems(list);

  ui->listWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);

  QObject::connect(ui->addPushButton, &QPushButton::clicked, this, [this](){
    ui->listWidget->addItem("A new item");
  });
  QObject::connect(ui->removePushButton, &QPushButton::clicked, this, [this](){
    ui->listWidget->takeItem(ui->listWidget->currentRow());
  });
  QObject::connect(ui->selectedPushButton, &QPushButton::clicked, this, [this](){
    QList<QListWidgetItem*> list = ui->listWidget->selectedItems();

    qDebug() << "Selected items:";
    for (int i=0; i<list.count();i++) {
      qDebug() << "Item: " << list.at(i)->text() << " at row: " << ui->listWidget->row(list.at(i));
    }
  });


}

Widget::~Widget () { delete ui; }
