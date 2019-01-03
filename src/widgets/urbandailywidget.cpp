#include "urbandailywidget.h"
#include <QVBoxLayout>
#include <QTimer>

UrbanDailyWidget::UrbanDailyWidget(QWidget *parent)
    : ContentFrame(parent),
      content_label_(new QLabel),
      urban_api_(new UrbanAPI)
{
    content_label_->setTextInteractionFlags(Qt::TextSelectableByMouse);
    content_label_->setWordWrap(true);

    addWidget(content_label_);
    addStretch();

    setContentsMargins(30, 20, 30, 30);

    QTimer::singleShot(100, urban_api_, &UrbanAPI::queryWordOfTheToday);

    connect(urban_api_, &UrbanAPI::queryWordOfTheTodayFinished,
            this, &UrbanDailyWidget::handleQueryWordOfDayFinished);
}

void UrbanDailyWidget::handleQueryWordOfDayFinished(QString word, QString meaning, QString example)
{
    content_label_->setText(QString("<p style=\"font-size: 22px;\">%1</p>"
                                    "<p>%2</p>"
                                    "<p>%3</p>"
                                    "From Urbandictionary's word of the day.")
                            .arg(word).arg(meaning).arg(example));
}
