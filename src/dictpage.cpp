#include "dictpage.h"

DictPage::DictPage(QWidget *parent)
    : QWidget(parent),
      youdao_dict_widget_(new YoudaoDictWidget)
{
    youdao_dict_widget_->setContentsMargins(25, 0, 25, 20);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(youdao_dict_widget_);
    setLayout(layout);
}

void DictPage::queryWord(const QString &text)
{
    youdao_dict_widget_->queryWord(text);
}

void DictPage::setFrameMargins(int left, int top, int right, int bottom)
{
    youdao_dict_widget_->setContentsMargins(left, top, right, bottom);
}
