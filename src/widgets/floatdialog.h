#ifndef FLOATDIALOG_H
#define FLOATDIALOG_H

#include <QWidget>
#include "../dictpage.h"

#ifdef Q_OS_LINUX
class EventMonitor;
#endif
class FloatDialog : public QWidget
{
    Q_OBJECT

public:
    explicit FloatDialog(QWidget *parent = nullptr);

    void popup(const QPoint &pos);
    void onGlobMousePress(const int &x, const int &y);
    void query(const QString &text);

protected:
    void keyPressEvent(QKeyEvent *);

private:
    DictPage *dict_page_;

#ifdef Q_OS_LINUX
    EventMonitor *event_monitor_;
#endif
};

#endif // FLOATDIALOG_H
