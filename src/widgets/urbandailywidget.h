#ifndef URBANDAILYWIDGET_H
#define URBANDAILYWIDGET_H

#include "../progresspage.h"
#include "../api/urbanapi.h"
#include "contentframe.h"

#include <QStackedLayout>
#include <QWidget>
#include <QLabel>

class UrbanDailyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit UrbanDailyWidget(QWidget *parent = nullptr);

private:
    void handleQueryWordOfDayFinished(QString, QString, QString);

private:
    QStackedLayout *stacked_layout_;
    ProgressPage *progress_page_;
    QLabel *content_label_;
    UrbanAPI *urban_api_;
};

#endif // URBANDAILYWIDGET_H
