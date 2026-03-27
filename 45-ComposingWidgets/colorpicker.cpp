#include "colorpicker.h"
#include <QPushButton>



ColorPicker::ColorPicker (QWidget *parent)
    : QWidget{ parent },
      gridLayout_{new QGridLayout{this}},
      previewLabel{new QLabel{this}} {

  this->populateColors();
  this->setupUi();

}

QColor ColorPicker::color() const {
  return color_;
}

void ColorPicker::setColor(const QColor& newColor) {
  if (this->color_ != newColor) {
    this->color_ = newColor;

    // Change the preview label to show the selected color
    const QString css = QString("background-color: %1").arg(this->color_.name());
    this->previewLabel->setStyleSheet(css);
    emit colorChanged(this->color_);
  }
}

void ColorPicker::handleColorButtonClicked() {
  auto* button = qobject_cast<QPushButton*>(this->sender());
  if (button) {
    const int index = button->property("colorIndex").toInt(); // property is a QVariant, you can cast it by using .toXXX method
    if (index >= 0 && index < this->colorList_.size()) {
      this->setColor(this->colorList_[index]);
    }
  }
}

void ColorPicker::populateColors() {
  this->colorList_ = {
    QColor("#FF0000"),  // Red
    QColor("#00FF00"),  // Green
    QColor("#0000FF"),  // Blue
    QColor("#FFFF00"),  // Yellow
    QColor("#FF00FF"),  // Magenta
    QColor("#00FFFF"),  // Cyan
    QColor("#FFA500"),  // Orange
    QColor("#800080"),  // Purple
    QColor("#008000")   // Dark Green
  };

}

void ColorPicker::setupUi() {
  this->setLayout(this->gridLayout_); // because of this, you don't have to specify "this", when initializing the gridLayout_
  this->previewLabel->setMinimumSize(200, 50);
  this->previewLabel->setFrameStyle(QFrame::Panel|QFrame::Sunken);
  this->previewLabel->setAlignment(Qt::AlignHCenter);
  this->gridLayout_->addWidget(this->previewLabel, 0, 0, 1, 3);


  //create the buttons
  for (int i=0; i<this->colorList_.size();++i) {
    auto* button = new QPushButton{this};
    button->setFixedSize(60,60);
    button->setProperty("colorIndex", i);

    const QString css = QString(R"(
                                   QPushButton {
                                       background-color: %1;
                                       border: 2px solid transparent;
                                       border-radius: 5px;
                                   }
                                   QPushButton:hover {
                                       border: 2px solid white;
                                       border-radius: 5px;
                                   }
                                   QPushButton:pressed {
                                       border: 3px solid white;
                                   }
                               )").arg(this->colorList_[i].name());
    button->setStyleSheet(css);

    QObject::connect(button, &QPushButton::clicked, this, &ColorPicker::handleColorButtonClicked);

    this->gridLayout_->addWidget(button, (i/3) + 1,i % 3);



  }
}















