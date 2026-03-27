#include "widget.h"
#include "./ui_widget.h"
#include <QInputDialog>

// #define DOUBLE
// #define ITEM
 #define INTEGER

Widget::Widget (QWidget *parent) : QWidget (parent), ui (new Ui::Widget) {
  ui->setupUi (this);

  QObject::connect(ui->pushButton, &QPushButton::clicked, this, [this](){


#if defined(DOUBLE)
    bool ok;
    double d = QInputDialog::getDouble(this, tr("QInputDialog::getDouble()"), tr("Amount:"), 37.56, -10000, 10000, 2, &ok);
    if (ok) {
        qDebug() << "Your double value is " << QString::number(d);
    }
#elif defined(ITEM)
    QStringList items;
    items << tr("Spring") << tr("Summer") << tr("Fall") << tr("Winter");
    bool ok;
    QString item = QInputDialog::getItem(this, tr("QInputDialog::getItem()"),tr("Season:"), items, 0, false, &ok);
    if (ok && !item.isEmpty()) {
      qDebug() << "Your chosen item is "<< item;
    }
  });
#elif defined(INTEGER)
    bool ok;
    int intItem = QInputDialog::getInt(this, tr("QInputDialog::getInt()"),tr("Percentage:"), 25, 0, 100, 1, &ok);
    if (ok) {
      qDebug() << "Your chosen item is "<< intItem;
    }
  });
#endif

/*ALL AVAILABLE methods in the QInputDialog class
 double getDouble(QWidget *parent, const QString &title, const QString &label, double value = 0, double min = -2147483647, double max = 2147483647, int decimals = 1, bool *ok = nullptr, Qt::WindowFlags flags = Qt::WindowFlags(), double step = 1)
 int getInt(QWidget *parent, const QString &title, const QString &label, int value = 0, int min = -2147483647, int max = 2147483647, int step = 1, bool *ok = nullptr, Qt::WindowFlags flags = Qt::WindowFlags())
 QString getItem(QWidget *parent, const QString &title, const QString &label, const QStringList &items, int current = 0, bool editable = true, bool *ok = nullptr, Qt::WindowFlags flags = Qt::WindowFlags(), Qt::InputMethodHints inputMethodHints = Qt::ImhNone)
 QString getMultiLineText(QWidget *parent, const QString &title, const QString &label, const QString &text = QString(), bool *ok = nullptr, Qt::WindowFlags flags = Qt::WindowFlags(), Qt::InputMethodHints inputMethodHints = Qt::ImhNone)
 QString getText(QWidget *parent, const QString &title, const QString &label, QLineEdit::EchoMode mode = QLineEdit::Normal, const QString &text = QString(), bool *ok = nullptr, Qt::WindowFlags flags = Qt::WindowFlags(), Qt::InputMethodHints inputMethodHints = Qt::ImhNone)

 */
}

Widget::~Widget () { delete ui; }
