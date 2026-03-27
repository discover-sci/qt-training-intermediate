#include "widget.h"
#include "./ui_widget.h"

Widget::Widget (QWidget *parent) : QWidget (parent), ui (new Ui::Widget) {
  ui->setupUi (this);

  this->colorList = QColor::colorNames();
  this->model = new QStringListModel(this->colorList,this);

  ui->listView->setModel(model);

  ui->listView->setMinimumWidth(10);


  QObject::connect(ui->listView, &QListView::clicked, this, [this](const QModelIndex &index){
    QPixmap pixmap(ui->label->size());

    // get the name of the color
    auto colorString = this->model->data(index, Qt::DisplayRole).toString();
    pixmap.fill(QColor(colorString));
    ui->label->setPixmap(pixmap);

    //qDebug() << "Our data: "<<  model->stringList();
    qDebug() << "Our data (current): " << colorString; //This will print the currently selected color
    qDebug() << "Our data: " << colorList;


  });
  ui->splitter->setChildrenCollapsible(false);
  ui->splitter->setCollapsible(0, false);   // left side cannot collapse
  ui->splitter->setHandleWidth(8);

  ui->splitter->widget(0)->setMinimumWidth(2);  // left panel min width
}

Widget::~Widget () { delete ui; }
