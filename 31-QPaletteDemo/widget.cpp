#include "widget.h"
#include "./ui_widget.h"
#include <QDebug>

Widget::Widget (QWidget *parent) : QWidget (parent), ui (new Ui::Widget) {
  ui->setupUi (this);

  // enable the option for the background of the QWidget to change
  ui->label->setAutoFillBackground(true);

         // get the palette from the widget
  QPalette palette = ui->label->palette();

         // change some properties on the palette
  palette.setColor(QPalette::Window, Qt::black);
  palette.setColor(QPalette::WindowText, Qt::yellow);

         // set the new palette with changed properties
  ui->label->setPalette(palette);

  QObject::connect(ui->activePushButton, &QPushButton::clicked, this, [this](){

    // both types of buttons have different color palettes
    QPalette::ColorGroup activeButtoncolorGroup = ui->activePushButton->palette().currentColorGroup();
    QPalette::ColorGroup inactiveButtoncolorGroup = ui->inactivePushButton->palette().currentColorGroup();

    qDebug() << "Active button color group: " << activeButtoncolorGroup;
    qDebug() << "Inactive button color group: " << inactiveButtoncolorGroup;



  });




}

Widget::~Widget () { delete ui; }
