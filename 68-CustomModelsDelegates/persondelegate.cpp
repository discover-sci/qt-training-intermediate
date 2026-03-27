#include "persondelegate.h"
#include <QStyledItemDelegate>
#include <QComboBox>

PersonDelegate::PersonDelegate (QObject *parent)
    : QStyledItemDelegate{parent} {

}


// void PersonDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
// {
// }

// QSize PersonDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
// {
// }

QWidget* PersonDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const {
  if (index.column() == 2) {

    // our editor for the values in the 2nd column
    QComboBox* comboBox = new QComboBox{parent};

    // build a combobox, populated with color icons and color names
    for (const QString &color : QColor::colorNames()) {
      QPixmap pix{50, 50};
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














