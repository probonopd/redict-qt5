#ifndef URBANDICTWIDGET_H
#define URBANDICTWIDGET_H

#include <QStackedLayout>
#include <QLabel>

#include "../progresspage.h"
#include "../api/urbanapi.h"
#include "contentframe.h"

class UrbanDictWidget : public QWidget
{
    Q_OBJECT

public:
    explicit UrbanDictWidget(QWidget *parent = nullptr);

    void queryText(const QString &text);

private:
    void handleQueryTextFinished(QString, QString, QString, QString, QString);

private:
    QStackedLayout *stacked_layout_;
    ProgressPage *progress_page_;
    QLabel *define_label_;
    UrbanAPI *urban_api_;
};

#endif // URBANDICTWIDGET_H
