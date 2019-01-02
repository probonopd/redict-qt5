#include "dailypage.h"
#include "utils.h"
#include <QVBoxLayout>
#include "widgets/youdaodailywidget.h"
#include "widgets/urbandailywidget.h"

DailyPage::DailyPage(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);
    setLayout(layout);

    if (Utils::isChinese()) {
        layout->addWidget(new YoudaoDailyWidget);
    } else {
        layout->addWidget(new UrbanDailyWidget);
    }
}
