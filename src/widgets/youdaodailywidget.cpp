#include "youdaodailywidget.h"
#include <QVBoxLayout>
#include <QTimer>

YoudaoDailyWidget::YoudaoDailyWidget(QWidget *parent)
    : QWidget(parent),
      youdao_api_(new YoudaoAPI),
      image_label_(new QLabel),
      title_label_(new QLabel),
      summary_label_(new QLabel),
      datetime_label_(new QLabel),
      stacked_layout_(new QStackedLayout),
      progress_page_(new ProgressPage)
{
    QWidget *main_widget = new QWidget;
    QVBoxLayout *main_layout = new QVBoxLayout(main_widget);
    QVBoxLayout *content_layout = new QVBoxLayout;

    image_label_->setScaledContents(true);

    content_layout->setContentsMargins(20, 0, 20, 0);
    content_layout->addWidget(summary_label_);
    content_layout->addWidget(title_label_);
    content_layout->addWidget(datetime_label_);

    main_layout->setMargin(0);
    main_layout->addWidget(image_label_);
    main_layout->addSpacing(20);
    main_layout->addLayout(content_layout);
    main_layout->addSpacing(20);
    main_layout->addStretch();

    stacked_layout_->addWidget(progress_page_);
    stacked_layout_->addWidget(main_widget);

    progress_page_->switchToProgress();

    setLayout(stacked_layout_);

    connect(youdao_api_, &YoudaoAPI::dailyFinished, this, &YoudaoDailyWidget::handleDailyFinished);
    connect(youdao_api_, &YoudaoAPI::loadImageFinsihed, this, &YoudaoDailyWidget::handleLoadImageFinsihed);
    connect(youdao_api_, &YoudaoAPI::dailyNetworkError, this, &YoudaoDailyWidget::handleNetworkError);
    connect(progress_page_, &ProgressPage::reloadButtonClicked, this, &YoudaoDailyWidget::reload);

    QTimer::singleShot(100, youdao_api_, &YoudaoAPI::queryDaily);
}

void YoudaoDailyWidget::handleDailyFinished(std::tuple<QString, QString, QString, QString, QString> datas)
{
    title_label_->setText(std::get<0>(datas));
    summary_label_->setText(std::get<1>(datas));
    datetime_label_->setText(std::get<2>(datas));

    youdao_api_->loadImage(std::get<4>(datas));
}

void YoudaoDailyWidget::handleLoadImageFinsihed(const QByteArray &data)
{
    QPixmap pixmap;
    pixmap.loadFromData(data);
    image_label_->setPixmap(pixmap);

    progress_page_->stop();
    stacked_layout_->setCurrentIndex(1);
}

void YoudaoDailyWidget::handleNetworkError()
{
    stacked_layout_->setCurrentIndex(0);
    progress_page_->switchToError();
}

void YoudaoDailyWidget::reload()
{
    stacked_layout_->setCurrentIndex(0);
    progress_page_->switchToProgress();

    QTimer::singleShot(100, youdao_api_, &YoudaoAPI::queryDaily);
}

