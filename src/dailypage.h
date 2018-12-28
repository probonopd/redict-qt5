#ifndef DAILYPAGE_H
#define DAILYPAGE_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include "youdaoapi.h"

class DailyPage : public QWidget
{
    Q_OBJECT

public:
    explicit DailyPage(QWidget *parent = nullptr);

private:
    void handleDailyFinished(std::tuple<QString, QString, QString, QString, QString>);
    void handleLoadImageFinsihed(const QByteArray &data);

private:
    YoudaoAPI *youdao_api_;
    QLineEdit *query_edit_;
    QLabel *image_label_;
    QLabel *title_label_;
    QLabel *summary_label_;
    QLabel *datetime_label_;
};

#endif
