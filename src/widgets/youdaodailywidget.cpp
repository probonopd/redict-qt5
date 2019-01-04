#include "youdaodailywidget.h"
#include <QVBoxLayout>
#include <QTimer>
#include <QDebug>
#include <QDir>

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

    image_cache_path_ = QString("%1/%2.jpeg")
            .arg(QFileInfo(settings_.fileName()).absolutePath())
            .arg(std::get<2>(datas));

    if (!QFile(image_cache_path_).exists()) {
        // auto clear image cache.
        clearImageCache();
        youdao_api_->loadImage(std::get<4>(datas));
    } else {
        // open image cache file.
        QFile cache_file(image_cache_path_);
        if (cache_file.open(QIODevice::ReadOnly)) {
            QByteArray image_data = cache_file.readAll();
            if (image_data.isEmpty()) {
                clearImageCache();
                // youdao_api_->queryDaily();
                handleNetworkError();
                return;
            }

            loadImage(image_data);
        }
        cache_file.close();
    }
}

void YoudaoDailyWidget::handleLoadImageFinsihed(const QByteArray &data)
{
    loadImage(data);

    // save image cache.
    QFile file(image_cache_path_);
    if (file.open(QIODevice::Append)) {
        file.write(data);
    }
    file.close();
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

void YoudaoDailyWidget::clearImageCache()
{
    QDir cache_dir(QFileInfo(settings_.fileName()).absolutePath());
    QFileInfoList file_list = cache_dir.entryInfoList(QDir::Files);

    for (const QFileInfo &file : file_list) {
        // do not delete the configuration file.
        if (file.filePath() == settings_.fileName()) {
            continue;
        }

        QFile f(file.filePath());
        f.remove();
        f.close();
    }
}

void YoudaoDailyWidget::loadImage(const QByteArray &data)
{
    QPixmap pixmap;
    pixmap.loadFromData(data);
    image_label_->setPixmap(pixmap);

    progress_page_->stop();
    stacked_layout_->setCurrentIndex(1);
}

