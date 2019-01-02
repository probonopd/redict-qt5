#ifndef URBANDICTWIDGET_H
#define URBANDICTWIDGET_H

#include <QLabel>
#include "contentframe.h"
#include "../api/urbanapi.h"

class UrbanDictWidget : public ContentFrame
{
    Q_OBJECT

public:
    explicit UrbanDictWidget(QWidget *parent = nullptr);

    void queryText(const QString &text);

private:
    void handleQueryTextFinished(QString, QString, QString, QString, QString);

private:
    QLabel *define_label_;
    UrbanAPI *urban_api_;
};

#endif // URBANDICTWIDGET_H
