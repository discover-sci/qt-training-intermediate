#include "widget.h"
#include "./ui_widget.h"

Widget::Widget (QWidget *parent) : QWidget (parent), ui (new Ui::Widget) {
  ui->setupUi (this);

  // our model
  table.append({"John","Doe","32","Farmer","Single","Gounduana","Mestkv","89"});
  table.append({"Mary","Jane","27","Teacher","Married","Verkso","Tukk","55"});
  table.append({"John","Doe","32","Farmer","Single","Gounduana","Mestkv","67"});
  table.append({"Mary","Jane","27","Teacher","Married","Verkso","Tukk","78"});
  table.append({"John","Doe","32","Farmer","Single","Gounduana","Mestkv","51"});
  table.append({"Mary","Jane","27","Teacher","Married","Verkso","Tukk","83"});
  table.append({"John","Doe","32","Farmer","Single","Gounduana","Mestkv","59"});
  table.append({"Mary","Jane","27","Teacher","Married","Verkso","Tukk","62"});
  table.append({"John","Doe","32","Farmer","Single","Gounduana","Mestkv","69"});
  table.append({"Mary","Jane","27","Teacher","Married","Verkso","Tukk","58"});
  table.append({"John","Doe","32","Farmer","Single","Gounduana","Mestkv","73"});
  table.append({"Mary","Jane","27","Teacher","Married","Verkso","Tukk","83"});
  table.append({"John","Doe","32","Farmer","Single","Gounduana","Mestkv","71"});
  table.append({"Mary","Jane","27","Teacher","Married","Verkso","Tukk","65"});
  table.append({"John","Doe","32","Farmer","Single","Gounduana","Mestkv","77"});
  table.append({"Mary","Jane","27","Teacher","Married","Verkso","Tukk","64"});
  table.append({"John","Doe","32","Farmer","Single","Gounduana","Mestkv","88"});
  table.append({"Mary","Jane","27","Teacher","Married","Verkso","Tukk","86"});
  table.append({"John","Doe","32","Farmer","Single","Gounduana","Mestkv","58"});
  table.append({"Mary","Jane","27","Teacher","Married","Verkso","Tukk","72"});

  QStringList labels;

  labels << "First Name"<<"Last Name"<<"Age"<<"Proffession"<<"Marital Status"<<"Country"<<"City"<<"Social Score";

  ui->tableWidget->setHorizontalHeaderLabels(labels);

  int noRows = table.size();
  int noColumns = table[0].size();

  for(int row = 0; row < noRows; ++row) {
    this->newRow();

    for( int col = 0; col < noColumns; ++col){
      // We are in a table cell (of type QTableWidgetItem). Set a value for it.
      ui->tableWidget->item(row,col)->setText(table[row][col]);
    }
  }

  // ui->tableWidget->setAlternatingRowColors(true);

  // ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

  // ui->tableWidget->horizontalHeader()->setMinimumSectionSize(
  //     ui->tableWidget->horizontalHeader()->fontMetrics().horizontalAdvance("Marital Status")
  //     );


  int minWidth = ui->tableWidget->verticalHeader()->width(); // row numbers
  minWidth += ui->tableWidget->frameWidth() * 2;

  for (int col = 0; col < ui->tableWidget->columnCount(); ++col) {
    minWidth += ui->tableWidget->columnWidth(col);
  }

  // Optional: add scrollbar width if needed
  minWidth += ui->tableWidget->style()->pixelMetric(QStyle::PM_ScrollBarExtent);

  // Apply to parent widget
  this->setMinimumWidth(minWidth);


}

Widget::~Widget () {
  delete ui;
}


/*
 New row in the QTableWidget means to insert a row adn create a QTableWidgetItem in each column
 */


void Widget::newRow() {
  int nextRowPosition = ui->tableWidget->rowCount();

  // enter a new row only at the location newRow
  ui->tableWidget->insertRow(nextRowPosition);

  QTableWidgetItem* first = nullptr;

  // loop 8 times for adding 8 columns in the row
  for (int i =0; i < 8; ++i) {

    // first creat an item, that's gonna be put into a row
    QTableWidgetItem* item = new QTableWidgetItem; // no parent, since a parent for the item is indirectly defined via setItem() method
    if(i == 0) {
      first = item;
    }
    item->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
    ui->tableWidget->setItem(nextRowPosition, i, item); // setItem() transfers ownership of item to QTableWidget
  }
  if (first){
    ui->tableWidget->setCurrentItem(first);
  }

}


