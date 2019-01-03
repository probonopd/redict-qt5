#ifndef URBANDAILYWIDGET_H
#define URBANDAILYWIDGET_H

#include <QWidget>
#include <QLabel>
#include "contentframe.h"
#include "../api/urbanapi.h"

class UrbanDailyWidget : public ContentFrame
{
    Q_OBJECT

public:
    explicit UrbanDailyWidget(QWidget *parent = nullptr);

private:
    void handleQueryWordOfDayFinished(QString, QString, QString);

private:
    QLabel *content_label_;
    UrbanAPI *urban_api_;
};

#endif // URBANDAILYWIDGET_H
