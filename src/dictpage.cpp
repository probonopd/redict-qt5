#include "dictpage.h"
#include <QLabel>

DictPage::DictPage(QWidget *parent)
    : QWidget(parent),
      youdao_api_(new YoudaoAPI),
      word_label_(new QLabel),
      explains_label_(new QLabel),
      voice_player_(new QMediaPlayer)
{
    us_voice_btn_ = new ImageButton(":/images/audio-normal.svg",
                                  ":/images/audio-hover.svg",
                                  ":/images/audio-press.svg");

    uk_voice_btn_ = new ImageButton(":/images/audio-normal.svg",
                                    ":/images/audio-hover.svg",
                                    ":/images/audio-press.svg");

    us_voice_label_ = new QLabel;
    uk_voice_label_ = new QLabel;

    frame_ = new QScrollArea;
    frame_layout_ = new QVBoxLayout;
    QWidget *frame_widget = new QWidget;
    QVBoxLayout *main_layout = new QVBoxLayout;

    QHBoxLayout *voice_layout = new QHBoxLayout;
    voice_layout->addWidget(uk_voice_btn_);
    voice_layout->addSpacing(5);
    voice_layout->addWidget(uk_voice_label_);
    voice_layout->addSpacing(50);
    voice_layout->addWidget(us_voice_btn_);
    voice_layout->addSpacing(5);
    voice_layout->addWidget(us_voice_label_);
    voice_layout->addStretch();

    uk_voice_btn_->hide();
    us_voice_btn_->hide();
    us_voice_label_->hide();
    uk_voice_label_->hide();

    word_label_->setWordWrap(true);
    explains_label_->setWordWrap(true);

    word_label_->setStyleSheet("QLabel { font-size: 20px; }");
    word_label_->setTextInteractionFlags(Qt::TextSelectableByMouse);
    explains_label_->setTextInteractionFlags(Qt::TextSelectableByMouse);

    frame_layout_->setContentsMargins(30, 10, 30, 20);
    frame_layout_->setSpacing(0);
    frame_layout_->addWidget(word_label_);
    frame_layout_->addSpacing(5);
    frame_layout_->addLayout(voice_layout);
    frame_layout_->addSpacing(10);
    frame_layout_->addWidget(explains_label_);
    frame_layout_->addStretch();
    frame_widget->setLayout(frame_layout_);

    frame_->setWidgetResizable(true);
    frame_->setWidget(frame_widget);

    main_layout->setMargin(0);
    main_layout->setSpacing(0);
    main_layout->addWidget(frame_);
    setLayout(main_layout);

    connect(youdao_api_, &YoudaoAPI::searchFinished, this, &DictPage::queryWordFinished);
    connect(us_voice_btn_, &ImageButton::clicked, this, &DictPage::playUSVoice);
    connect(uk_voice_btn_, &ImageButton::clicked, this, &DictPage::playUKVoice);
}

void DictPage::queryWord(const QString &text)
{
    if (text != word_label_->text()) {
        uk_voice_btn_->hide();
        us_voice_btn_->hide();
        us_voice_label_->hide();
        uk_voice_label_->hide();

        youdao_api_->queryWord(text);
    }
}

void DictPage::setFrameMargins(int left, int top, int right, int bottom)
{
    frame_layout_->setContentsMargins(left, top, right, bottom);
}

void DictPage::queryWordFinished(std::tuple<QString, QString, QString, QString, QString> datas)
{
    const QString &word = std::get<0>(datas);
    const QString &uk_phonetic = std::get<1>(datas);
    const QString &us_phonetic = std::get<2>(datas);
    const QString &basic_explains = std::get<3>(datas);
    const QString &web_references = std::get<4>(datas);

    if (uk_phonetic.isEmpty()) {
        uk_voice_btn_->hide();
        uk_voice_label_->hide();
    } else {
        uk_voice_btn_->show();
        uk_voice_label_->show();
        uk_voice_label_->setText(QString("%1 [%2]").arg(tr("UK"), uk_phonetic));
    }

    if (us_phonetic.isEmpty()) {
        us_voice_btn_->hide();
        us_voice_label_->hide();
    } else {
        us_voice_btn_->show();
        us_voice_label_->show();
        us_voice_label_->setText(QString("%1 [%2]").arg(tr("US"), us_phonetic));
    }

    word_label_->setText(word);

    QString contents;
    if (!basic_explains.isEmpty()) {
        contents += basic_explains;
        contents += "<br></br>";
    }

    contents += web_references;

    explains_label_->setText(contents);
}

void DictPage::playUSVoice()
{
    voice_player_->setMedia(QUrl("http://dict.youdao.com/dictvoice?type=2&audio=" + word_label_->text()));
    voice_player_->play();
}

void DictPage::playUKVoice()
{
    voice_player_->setMedia(QUrl("http://dict.youdao.com/dictvoice?type=1&audio=" + word_label_->text()));
    voice_player_->play();
}
