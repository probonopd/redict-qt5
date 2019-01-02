#ifndef DICTPAGE_H
#define DICTPAGE_H

#include <QWidget>
#include "widgets/youdaodictwidget.h"
#include "widgets/urbandictwidget.h"

class DictPage : public QWidget
{
    Q_OBJECT

public:
    explicit DictPage(QWidget *parent = nullptr);

    void queryWord(const QString &text);
    void setFrameMargins(int, int, int, int);

private:
    YoudaoDictWidget *youdao_dict_widget_;
    UrbanDictWidget *urban_dict_widget_;
};

#endif // DICTPAGE_H
