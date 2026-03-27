#include "widget.h"
#include "./ui_widget.h"
#include "childbutton.h"
#include <QDebug>
#include "chillineedit.h"

Widget::Widget (QWidget *parent) : QWidget (parent), ui (new Ui::Widget) {
  ui->setupUi (this);

  auto *button = new ChildButton{this};
  button->setText("Child Button");
  QObject::connect(button, &QPushButton::clicked, this, [this](){
    qDebug() << "WidgetParent mousePressEvent called.";
  });
  ui->verticalLayout->addWidget(button);

  auto *lineEdit = new ChilLineEdit{this};
  ui->verticalLayout->addWidget(lineEdit);

}

Widget::~Widget () { delete ui; }
