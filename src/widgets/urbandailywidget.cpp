#include "urbandailywidget.h"
#include <QVBoxLayout>
#include <QTimer>

UrbanDailyWidget::UrbanDailyWidget(QWidget *parent)
    : QWidget(parent),
      stacked_layout_(new QStackedLayout),
      progress_page_(new ProgressPage),
      content_label_(new QLabel),
      urban_api_(new UrbanAPI)
{
    ContentFrame *frame_widget = new ContentFrame;
    frame_widget->setContentsMargins(30, 20, 30, 30);
    frame_widget->addWidget(content_label_);
    frame_widget->addStretch();

    content_label_->setTextInteractionFlags(Qt::TextSelectableByMouse);
    content_label_->setWordWrap(true);

    progress_page_->switchToProgress();

    stacked_layout_->addWidget(progress_page_);
    stacked_layout_->addWidget(frame_widget);
    setLayout(stacked_layout_);

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

    stacked_layout_->setCurrentIndex(1);
    progress_page_->stop();
}
