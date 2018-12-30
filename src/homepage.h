#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QWidget>
#include <QLineEdit>
#include <QStackedLayout>
#include "dailypage.h"
#include "dictpage.h"

class QTimer;
class HomePage : public QWidget
{
    Q_OBJECT

public:
    explicit HomePage(QWidget *parent = nullptr);

private:
    void handleTextEdited();
    void handleEditReturnPressed();
    void queryWord();

private:
    QLineEdit *query_edit_;
    QStackedLayout *stacked_layout_;
    DailyPage *daily_page_;
    DictPage *dict_page_;
    QTimer *delay_timer_;
};

#endif // HOMEPAGE_H
