#ifndef INFODIALOG_H
#define INFODIALOG_H

#include <QDialog>

namespace Ui { class InfoDialog; }

class InfoDialog : public QDialog {
  Q_OBJECT

public:
  explicit InfoDialog (QWidget *parent = nullptr);
  ~InfoDialog ();

  QString position() const;
  void setPosition(const QString &newPosition);

  QString favoriteOS() const;
  void setFavoriteOS(const QString &newFavoriteOS);

private:
  Ui::InfoDialog *ui;
  QString position_;
  QString favoriteOS_;
};

#endif // INFODIALOG_H
