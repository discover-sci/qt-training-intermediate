#ifndef KEYBOARDFILTER_H
#define KEYBOARDFILTER_H

#include <QObject>

class KeyboardFilter : public QObject {
  Q_OBJECT
public:
  explicit KeyboardFilter (QObject *parent = nullptr);

signals:

  // QObject interface
protected:
  bool eventFilter(QObject *watched, QEvent *event) override;

private:
  static inline constexpr std::string_view ALLOWED_NUMBERS = "1234567890";
};

#endif // KEYBOARDFILTER_H
