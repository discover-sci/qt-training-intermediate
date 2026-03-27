#include "widget.h"
#include "./ui_widget.h"
#include <QHBoxLayout>

Widget::Widget (QWidget *parent) : QWidget (parent), ui (new Ui::Widget) {
  ui->setupUi (this);



  QObject::connect(ui->verticalButton, &QPushButton::clicked, this, [this]() {
    //Delete the old one
    if (this->layout())
      delete this->layout();

    // Define and set the new layout for the widget
    QVBoxLayout *vLayout = new QVBoxLayout(this); // Memory Leak ? No. memory gets released by whatever widget uses thsi layout
                                                   // Providing a parent does no harm

           //Add things to the layout
    vLayout->addWidget(ui->button1);
    vLayout->addWidget(ui->button2);
    vLayout->addWidget(ui->button3);
    vLayout->addWidget(ui->button4);
    vLayout->addWidget(ui->button5);

           //Set layout to widget and AT THE SAME TIME: set the ownership
    setLayout(vLayout); // the widget takes ownership over this layout and release it, when it is destroyed itself

  });

  QObject::connect(ui->horizontalButton, &QPushButton::clicked, this, [this]() {
    //Delete the old one
    if (this->layout())
      delete this->layout();

    // Define and set the new layout for the widget
    QHBoxLayout *hLayout = new QHBoxLayout(this); // Memory Leak ? No. memory gets released by whatever widget uses thsi layout
                                                   // Providing a parent does no harm

    //Add things to the layout
    hLayout->addWidget(ui->button1);
    hLayout->addWidget(ui->button2);
    hLayout->addWidget(ui->button3);
    hLayout->addWidget(ui->button4);
    hLayout->addWidget(ui->button5);

    // Set layout to widget and AT THE SAME TIME: set the ownership
    setLayout(hLayout); // the widget takes ownership over this layout and release it, when it is destroyed itself

  });



}

Widget::~Widget () { delete ui; }
