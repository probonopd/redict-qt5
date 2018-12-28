#include "dailypage.h"
#include <QVBoxLayout>
#include <QTimer>

DailyPage::DailyPage(QWidget *parent)
    : QWidget(parent),
      youdao_api_(new YoudaoAPI),
      query_edit_(new QLineEdit),
      image_label_(new QLabel),
      title_label_(new QLabel),
      summary_label_(new QLabel),
      datetime_label_(new QLabel)
{
    QVBoxLayout *main_layout = new QVBoxLayout;
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

    setLayout(main_layout);

    connect(youdao_api_, &YoudaoAPI::dailyFinished, this, &DailyPage::handleDailyFinished);
    connect(youdao_api_, &YoudaoAPI::loadImageFinsihed, this, &DailyPage::handleLoadImageFinsihed);

    QTimer::singleShot(1, youdao_api_, &YoudaoAPI::queryDaily);
}

void DailyPage::handleDailyFinished(std::tuple<QString, QString, QString, QString, QString> datas)
{
    title_label_->setText(std::get<0>(datas));
    summary_label_->setText(std::get<1>(datas));
    datetime_label_->setText(std::get<2>(datas));

    // fix appimage?
    QTimer::singleShot(10, this, [=] { youdao_api_->loadImage(std::get<4>(datas)); });
}

void DailyPage::handleLoadImageFinsihed(const QByteArray &data)
{
    QPixmap pixmap;
    pixmap.loadFromData(data);
    image_label_->setPixmap(pixmap);
}
