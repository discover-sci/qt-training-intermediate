#include "widget.h"
#include "./ui_widget.h"

Widget::Widget (QWidget *parent) : QWidget (parent), ui (new Ui::Widget) {
  ui->setupUi (this);

  // To add a new widget to a TabWidget, means to create a completely new Widget, define its behaviour
  // layouts and all the buttons, stretches, add spacers, define signals for widgets and so on ... and finally,
  // when Widget is all set insert it into a tab widget

  //Declare the widget
  QWidget* widget = new QWidget(this);

  //Declare the layout for the widget
  QVBoxLayout* layout = new QVBoxLayout();

  layout->addWidget(new QPushButton("Button1",this));
  layout->addWidget(new QPushButton("Button2",this));
  layout->addWidget(new QPushButton("Button3",this));
  QPushButton* button4 = new QPushButton("Button4",this);

  connect(button4, &QPushButton::clicked, this, [this]() {
    qDebug() << "Button4 from custom tab clicked";
  });

  layout->addWidget(button4);
  layout->addSpacerItem(new QSpacerItem(100,200));

  //Set the layout to the widget
  widget->setLayout(layout);

  //Add the widget to the layout
  //ui->tabWidget->addTab(widget,"Tab 4");
  ui->tabWidget->insertTab(0, widget, "Users");
}


Widget::~Widget () { delete ui; }
