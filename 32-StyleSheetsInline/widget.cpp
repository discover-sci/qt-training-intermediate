#include "widget.h"
#include "./ui_widget.h"
#include "dialog.h"

Widget::Widget (QWidget *parent) : QWidget (parent), ui (new Ui::Widget) {
  ui->setupUi (this);

  // stylesheet per widget
  /*
  // ui->pushButton->setStyleSheet("QPushButton{"
  //                               "background-color: yellow;"
  //                               "color: red;"
  //                               "}");
  */

  // this->setStyleSheet("QPushButton{"
  //                               "background-color: yellow;"
  //                               "color: red;"
  //                               "}");


  QObject::connect(ui->dialogPushButton, &QPushButton::clicked, this, [this](){
    Dialog *myDialog = new Dialog{this};

    // all the widgets under dialog will have this particular stylesheet set up
    myDialog->setStyleSheet("QPushButton{"
                            "background-color: yellow;"
                            "color: red;"
                            "}");
    myDialog->exec();
  });

}

Widget::~Widget () { delete ui; }
