#include "persondelegate.h"
#include <QStyledItemDelegate>
#include <QComboBox>

PersonDelegate::PersonDelegate (QObject *parent)
    : QStyledItemDelegate{parent} {

}


/*
 option in a delegate’s paint() method is a QStyleOptionViewItem, and it contains everything the delegate needs to
 know about how the cell should be drawn. It is not “just some parameter” — it is the full description of the cell’s visual state.
 */
/*

 */
void PersonDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
  if (index.column() == 2){
    // get the favorite color for use in a column that saves favoriteColor
    QString favColor = index.data(PersonModel::FavoriteColorRole).toString();


    painter->save();

    // get the fill Color; brush color is basically a fill color
    painter->setBrush(QBrush(QColor(favColor)));

    // draw a retangle which will have a colored rectangle inside
    painter->drawRect(option.rect.adjusted(3,3,-3,-3));

    // get the text size... QSize is 2D pair
    QSize textSize = option.fontMetrics.size(Qt::TextSingleLine,favColor);
    painter->setBrush(QBrush(Qt::white));
    painter->setPen(Qt::black);

    // Compute the width and height adjustments
    int widthAdjust = ((option.rect.width() - textSize.width())/2 - 3);
    int heightAdjust = ((option.rect.height() - textSize.height())/2);

    painter->drawRect(option.rect.adjusted(widthAdjust, heightAdjust, -widthAdjust, -heightAdjust));
    painter->drawText(option.rect, favColor, Qt::AlignHCenter | Qt::AlignVCenter);

    painter->restore();


  } else {
    QStyledItemDelegate::paint(painter, option, index);
  }

}

QSize PersonDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const {
  return QStyledItemDelegate::sizeHint(option, index).expandedTo(QSize(84, option.fontMetrics.height() + 10));
}

QWidget* PersonDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const {
  if (index.column() == 2) {

    // our editor for the values in the 2nd column
    QComboBox* comboBox = new QComboBox{parent};

    // build a combobox, populated with color icons and color names
    for (QString &color : QColor::colorNames()) {
      QPixmap pix{50,50};
      pix.fill(QColor{color});
      comboBox->addItem(QIcon{pix}, color);
    }
    return comboBox;
  } else {
    return QStyledItemDelegate::createEditor(parent, option, index);
  }
}

// reading data from the model and display it in the editor widget, which is a QComboBox in our case
void PersonDelegate::setEditorData(QWidget* editor, const QModelIndex &index) const {
  if (index.column() == 2) {
    QComboBox* combo = static_cast<QComboBox*>(editor); // Editor sent into this method could be anything. We know we are going to be using QComboBox, so cast it accordingly.
    auto colorList = QColor::colorNames();
    auto currentColorStringSelected = index.data(Qt::DisplayRole).toString(); // read current value for selected color
    auto idx = colorList.indexOf(currentColorStringSelected);
    combo->setCurrentIndex(idx);
  } else {
    QStyledItemDelegate::setEditorData(editor, index);
  }
}

// read the data from the editor and write it into a model
void PersonDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const {
  if (index.column() == 2) {
    QComboBox* combo = static_cast<QComboBox*>(editor); // Editor sent into this method could be anything. We know we are going to be using QComboBox, so cast it accordingly.

    // use the existing setData() method (defined before) on a model - passed here as a parameter
    model->setData(index, combo->currentText(), Qt::EditRole);  // combo->currentText() is the value to set into a model

    // alternative approach - you just need to specify WHAT you want to set via role
    // model->setData(index, combo->currentText(), PersonModel::FavoriteColorRole);


  } else {
    return QStyledItemDelegate::setModelData(editor, model, index);
  }
}

void PersonDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const {

  editor->setGeometry(option.rect);

}














