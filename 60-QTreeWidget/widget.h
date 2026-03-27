#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTreeWidgetItem>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget {
  Q_OBJECT

public:
  Widget (QWidget *parent = nullptr);
  ~Widget ();

private:
  Ui::Widget *ui;
  QTreeWidgetItem *addRootOrganization(QString company, QString purpose);
  QTreeWidgetItem *addChildOrganization(QTreeWidgetItem *parent,QString branch,QString description);
};
#endif // WIDGET_H
