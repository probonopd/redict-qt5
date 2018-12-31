#ifndef FLOATDIALOG_H
#define FLOATDIALOG_H

#include <QWidget>
#include "../dictpage.h"

class FloatDialog : public QWidget
{
    Q_OBJECT

public:
    explicit FloatDialog(QWidget *parent = nullptr);

    void popup(const QPoint &pos);
    void query(const QString &text);

protected:
    void keyPressEvent(QKeyEvent *);

private:
    DictPage *dict_page_;
};

#endif // FLOATDIALOG_H
