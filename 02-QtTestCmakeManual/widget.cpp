#include "widget.h"
#include "./ui_widget.h"
#include "QPushButton"
#include "QVBoxLayout"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    QPushButton *btn = new QPushButton("Click me", this);
    btn->setGeometry(20, 20, 120, 40); // x, y, width, height

    // VBox layout
    // auto *layout = new QVBoxLayout(this);
    // auto *btn1 = new QPushButton("Button 1");
    // auto *btn2 = new QPushButton("Button 2");
    // layout->addWidget(btn1);
    // layout->addWidget(btn2);
    // this->setLayout(layout);

    // Mesanica VBox in HBox layout
    // auto *mainLayout = new QHBoxLayout(this);
    // auto *leftLayout = new QVBoxLayout();
    // auto *rightLayout = new QGridLayout();
    // mainLayout->addLayout(leftLayout);
    // mainLayout->addLayout(rightLayout);
    // leftLayout->addWidget(new QPushButton("Left 1"));
    // leftLayout->addWidget(new QPushButton("Left 2"));
    // rightLayout->addWidget(new QPushButton("R1"), 0, 0);
    // rightLayout->addWidget(new QPushButton("R2"), 0, 1);
    // setLayout(mainLayout);

    // Grid layout
    auto *grid = new QGridLayout(this);
    grid->addWidget(new QPushButton("Top Left"), 0, 0);
    grid->addWidget(new QPushButton("Top Right"), 0, 1);
    grid->addWidget(new QPushButton("Bottom Left"), 1, 0);
    grid->addWidget(new QPushButton("Bottom Right"), 1, 1);
    setLayout(grid);

}

Widget::~Widget()
{
    delete ui;
}
