#include "dictpage.h"
#include <QVBoxLayout>
#include <QScrollArea>
#include <QLabel>

DictPage::DictPage(QWidget *parent)
    : QWidget(parent),
      youdao_api_(new YoudaoAPI),
      word_label_(new QLabel),
      explains_label_(new QLabel),
      references_label_(new QLabel)
{
    QScrollArea *frame = new QScrollArea;
    QWidget *frame_widget = new QWidget;
    QVBoxLayout *frame_layout = new QVBoxLayout;
    QVBoxLayout *main_layout = new QVBoxLayout;

    word_label_->setWordWrap(true);
    explains_label_->setWordWrap(true);
    references_label_->setWordWrap(true);

    word_label_->setTextInteractionFlags(Qt::TextSelectableByMouse);
    explains_label_->setTextInteractionFlags(Qt::TextSelectableByMouse);
    references_label_->setTextInteractionFlags(Qt::TextSelectableByMouse);

    frame_layout->setContentsMargins(30, 20, 30, 20);
    frame_layout->setSpacing(0);
    frame_layout->addWidget(word_label_);
    frame_layout->addSpacing(10);
    frame_layout->addWidget(explains_label_);
    frame_layout->addWidget(references_label_);
    frame_layout->addStretch();
    frame_widget->setLayout(frame_layout);

    frame->setWidgetResizable(true);
    frame->setWidget(frame_widget);

    main_layout->setMargin(0);
    main_layout->setSpacing(0);
    main_layout->addWidget(frame);
    setLayout(main_layout);

    connect(youdao_api_, &YoudaoAPI::searchFinished, this, &DictPage::queryWordFinished);
}

void DictPage::queryWord(const QString &text)
{
    youdao_api_->queryWord(text);
}

void DictPage::queryWordFinished(std::tuple<QString, QString, QString, QString, QString> datas)
{
    word_label_->setText(std::get<0>(datas));
    explains_label_->setText(std::get<3>(datas));
    references_label_->setText(std::get<4>(datas));
}
