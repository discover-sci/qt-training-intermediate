#include "widget.h"
#include "./ui_widget.h"

Widget::Widget (QWidget *parent) : QWidget (parent), ui (new Ui::Widget) {
  ui->setupUi (this);

  this->colorList = QColor::colorNames();
  this->model = new QStringListModel(this->colorList,this);

  ui->listView->setModel(model);
  ui->listView->setMinimumWidth(10);

  this->proxyModel = new QSortFilterProxyModel(this);
  this->proxyModel->setSourceModel(model);

  ui->listView->setModel(proxyModel);

  QObject::connect(ui->lineEdit, &QLineEdit::textChanged, this, [this](const QString &filterString) {
    // this->proxyModel->setFilterRegularExpression(ui->lineEdit->text());
    // or
    this->proxyModel->setFilterRegularExpression(filterString);
  });

  QObject::connect(ui->listView, &QListView::clicked, this, [this](const QModelIndex &idx) {
    qDebug() << "Clicked index:" << idx;
    QString text = idx.data(Qt::DisplayRole).toString();
    ui->selectionLabel->setText(text);
  });


}

Widget::~Widget () { delete ui; }
