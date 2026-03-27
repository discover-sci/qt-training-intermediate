#include "widget.h"
#include "./ui_widget.h"
#include <QListWidgetItem>

Widget::Widget (QWidget *parent) : QWidget (parent), ui (new Ui::Widget) {
  ui->setupUi (this);

  // fill in your data
  this->fruitList << "Apple"  << "Avocado" << "Banana"
            << "Blueberries" << "Cucumber" << "EggFruit"
            << "Fig" << "Grape" << "Mango" << "Pear"
            << "Pineapple" << "Watermellon";

  // populate the QListWidget with icons
  for (QString &fruit : fruitList) {
    QListWidgetItem* item = new QListWidgetItem(fruit, ui->listWidget);
    QString filename = ":/images/" + fruit.toLower() + ".png";

    // set properties on item: data + icon + etc. ...
    item->setIcon(QIcon(filename));
    item->setData(Qt::DisplayRole,fruit);

  }

  // get the position of an item
  QObject::connect(ui->pushButton, &QPushButton::clicked, this, [this](){
    QString data = ui->listWidget->currentItem()->data(Qt::DisplayRole).toString();
    qDebug() << "Current item: " << data;
    qDebug() << "Current index: " << ui->listWidget->currentIndex().row(); // index returns
  });

  // populate only with text (no icons)
  // ui->listWidget->addItems(fruitList);
}

Widget::~Widget () { delete ui; }
