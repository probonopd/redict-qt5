#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QWidget>
#include <QLineEdit>
#include <QStackedLayout>
#include "dailypage.h"
#include "dictpage.h"

class HomePage : public QWidget
{
    Q_OBJECT

public:
    explicit HomePage(QWidget *parent = nullptr);

private:
    void handleTextEdited(QString);

private:
    QLineEdit *query_edit_;
    QStackedLayout *stacked_layout_;
    DailyPage *daily_page_;
    DictPage *dict_page_;
};

#endif // HOMEPAGE_H
