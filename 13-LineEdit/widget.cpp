#include "widget.h"
#include "./ui_widget.h"
#include "QLabel"
#include <QLineEdit>
#include <QPushButton>

Widget::Widget (QWidget *parent) : QWidget (parent), ui (new Ui::Widget) {
  ui->setupUi (this);

  //First Name
  QLabel *firstNameLabel = new QLabel("First Name",this);
  firstNameLabel->setMinimumSize(70,50);
  firstNameLabel->move(10,10);

  QLineEdit *firstNameLineEdit = new QLineEdit(this);
  firstNameLineEdit->setMinimumSize(200,50);
  firstNameLineEdit->move(100,10);

  //Lastname Name
  QLabel *lastNameLabel = new QLabel("Last Name",this);
  lastNameLabel->setMinimumSize(70,50);
  lastNameLabel->move(10,70);

  QLineEdit *lastNameLineEdit = new QLineEdit(this);
  lastNameLineEdit->setMinimumSize(200,50);
  lastNameLineEdit->move(100,70);


  //City
  QLabel * cityLabel = new QLabel("City",this);
  cityLabel->setMinimumSize(70,50);
  cityLabel->move(10,130);

  QLineEdit * cityLineEdit = new QLineEdit(this);
  cityLineEdit->setMinimumSize(200,50);
  cityLineEdit->move(100,130);

  QFont buttonFont("Times", 20, QFont::Bold);
  QPushButton * button = new QPushButton("Grab data",this);
  button->setFont(buttonFont);
  button->move(80,190);

  // here, the "=" char must be used in capture list. There are many local variables that must be captured,
  // not data members of the class
  connect(button, &QPushButton::clicked, this, [=]() {
      QString firstName = firstNameLineEdit->text();  // grab the text
      QString lastName = lastNameLineEdit->text();    // grab the text
      QString city = cityLineEdit->text();            // grab the text

      // check the data validity
      if( !firstName.isEmpty() && !lastName.isEmpty() && !city.isEmpty()) {
        //If neither field is empty we fall here
        qDebug() << " First name is : " << firstName;
        qDebug() << " Last name is : " << lastName;
        qDebug() << " City is : " << city;
      } else {
        qDebug() << "One field is empty ";
      }

  });

  //Respond to signals from QLineEdits

  //cursorPositionChanged
  connect(firstNameLineEdit, &QLineEdit::cursorPositionChanged, [=]() {
    qDebug() << "The current cursor position is: " << firstNameLineEdit->cursorPosition();
  });

  //editingFinished : emitted when user clicks enter or when line edit looses focus
  connect(firstNameLineEdit, &QLineEdit::editingFinished, [=]() {
    qDebug() << "Editing finished.";
  });

  //returnPressed in firstNameLineEdit
  connect(firstNameLineEdit, &QLineEdit::returnPressed, [=]() {
    qDebug() << "Return Pressed.";
    lastNameLineEdit->setFocus(); //set focus to the next LineEdit. Similar behaviour as Tab keypress

  });

  //returnPressed in lastNameLineEdit
  connect(lastNameLineEdit, &QLineEdit::returnPressed, [=]() {
    qDebug() << "Return Pressed.";
    cityLineEdit->setFocus(); //set focus to the next LineEdit. Similar behaviour as Tab keypress

  });


  //selectionChanged
  connect(firstNameLineEdit, &QLineEdit::selectionChanged, [=]() {
    qDebug() << "Selection Changed .";
  });

  //textChanged
  connect(firstNameLineEdit, &QLineEdit::textChanged, [=]() {
    qDebug() << "Selection Changed to :"  <<  firstNameLineEdit->text();
  });

  //textEdited
  connect(firstNameLineEdit,&QLineEdit::textEdited,[=](){
    qDebug() << "Selection edited and changed to :"  <<  firstNameLineEdit->text();
  });

  //Hint text for all three LineEdits
  firstNameLineEdit->setPlaceholderText("First name");
  lastNameLineEdit->setPlaceholderText("Last Name");
  cityLineEdit->setPlaceholderText("City");

  //Change text in QLineEdit programmaticaly
  lastNameLineEdit->setText("Say your last name"); // At the beginning, there is a default value in this line edit field


}

Widget::~Widget () { delete ui; }
