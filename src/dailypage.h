#ifndef DAILYPAGE_H
#define DAILYPAGE_H

#include <QWidget>
#include <QLabel>
#include <QStackedLayout>
#include "youdaoapi.h"
#include "progresspage.h"

class DailyPage : public QWidget
{
    Q_OBJECT

public:
    explicit DailyPage(QWidget *parent = nullptr);

private:
    void handleDailyFinished(std::tuple<QString, QString, QString, QString, QString>);
    void handleLoadImageFinsihed(const QByteArray &data);
    void handleNetworkError();
    void reload();

private:
    YoudaoAPI *youdao_api_;
    QLabel *image_label_;
    QLabel *title_label_;
    QLabel *summary_label_;
    QLabel *datetime_label_;

    QStackedLayout *stacked_layout_;
    ProgressPage *progress_page_;
};

#endif
