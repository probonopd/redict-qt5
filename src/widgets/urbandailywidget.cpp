#include "urbandailywidget.h"
#include <QVBoxLayout>
#include <QTimer>

UrbanDailyWidget::UrbanDailyWidget(QWidget *parent)
    : ContentFrame(parent),
      word_label_(new QLabel),
      meaning_label_(new QLabel),
      example_label_(new QLabel),
      tips_label_(new QLabel),
      urban_api_(new UrbanAPI)
{
    word_label_->setTextInteractionFlags(Qt::TextSelectableByMouse);
    meaning_label_->setTextInteractionFlags(Qt::TextSelectableByMouse);
    example_label_->setTextInteractionFlags(Qt::TextSelectableByMouse);
    tips_label_->setTextInteractionFlags(Qt::TextSelectableByMouse);

    word_label_->setWordWrap(true);
    meaning_label_->setWordWrap(true);
    example_label_->setWordWrap(true);

    word_label_->setStyleSheet("QLabel { font-size: 22px; }");

    addWidget(word_label_);
    addSpacing(10);
    addWidget(meaning_label_);
    addSpacing(5);
    addWidget(example_label_);
    addSpacing(10);
    addWidget(tips_label_);
    addStretch();

    tips_label_->setText("From Urbandictionary's word of the day.");
    tips_label_->hide();

    setContentsMargins(30, 20, 30, 30);

    QTimer::singleShot(100, urban_api_, &UrbanAPI::queryWordOfTheToday);

    connect(urban_api_, &UrbanAPI::queryWordOfTheTodayFinished,
            this, &UrbanDailyWidget::handleQueryWordOfDayFinished);
}

void UrbanDailyWidget::handleQueryWordOfDayFinished(QString word, QString meaning, QString example)
{
    word_label_->setText(word);
    meaning_label_->setText(meaning);
    example_label_->setText(example);

    tips_label_->show();
}
