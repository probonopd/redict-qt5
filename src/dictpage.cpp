#include "dictpage.h"
#include "utils.h"

DictPage::DictPage(QWidget *parent)
    : QWidget(parent),
      youdao_dict_widget_(new YoudaoDictWidget),
      urban_dict_widget_(new UrbanDictWidget)
{
    youdao_dict_widget_->setContentsMargins(25, 0, 25, 20);
    urban_dict_widget_->setContentsMargins(25, 0, 25, 20);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(youdao_dict_widget_);
    layout->addWidget(urban_dict_widget_);
    setLayout(layout);

    if (Utils::isChinese()) {
        youdao_dict_widget_->show();
        urban_dict_widget_->hide();
    } else {
        youdao_dict_widget_->hide();
        urban_dict_widget_->show();
    }
}

void DictPage::queryWord(const QString &text)
{
    if (Utils::isChinese()) {
        youdao_dict_widget_->queryWord(text);
    } else {
        urban_dict_widget_->queryText(text);
    }
}

void DictPage::setFrameMargins(int left, int top, int right, int bottom)
{
    youdao_dict_widget_->setContentsMargins(left, top, right, bottom);
    urban_dict_widget_->setContentsMargins(left, top, right, bottom);
}
