#include "urbandictwidget.h"
#include <QDebug>

UrbanDictWidget::UrbanDictWidget(QWidget *parent)
    : QWidget(parent),
      stacked_layout_(new QStackedLayout),
      progress_page_(new ProgressPage),
      define_label_(new QLabel),
      urban_api_(new UrbanAPI)
{
    ContentFrame *content_frame = new ContentFrame;
    content_frame->setContentsMargins(0, 0, 0, 0);
    content_frame->addWidget(define_label_);
    content_frame->addStretch();

    stacked_layout_->addWidget(progress_page_);
    stacked_layout_->addWidget(content_frame);

    define_label_->setTextInteractionFlags(Qt::TextSelectableByMouse);
    define_label_->setWordWrap(true);

    setLayout(stacked_layout_);

    connect(urban_api_, &UrbanAPI::queryTextFinished, this, &UrbanDictWidget::handleQueryTextFinished);
}

void UrbanDictWidget::queryText(const QString &text)
{
    progress_page_->switchToProgress();
    stacked_layout_->setCurrentIndex(0);

    urban_api_->queryText(text);
}

void UrbanDictWidget::handleQueryTextFinished(QString word, QString definition,
                                              QString example, QString author, QString datetime)
{
    QDateTime dt = QDateTime::fromString(datetime, Qt::ISODate);
    // QLocale locale(QLocale::English, QLocale::UnitedStates);
    QString content;

    content += QString("<p style=\"font-size: 22px;\">%1</p>").arg(word);
    content += QString("<p>%1</p>").arg(definition);
    content += QString("<p>%1</p>").arg(example);
    content += QString("<p>by %1 %2</p>").arg(author).arg(dt.toString("MMM dd yyyy"));

    define_label_->setText(content);
    stacked_layout_->setCurrentIndex(1);
    progress_page_->stop();
}
