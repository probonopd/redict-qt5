#include "translatepage.h"
#include "mainwindow.h"
#include <QVBoxLayout>
#include <QKeyEvent>

TranslatePage::TranslatePage(QWidget *parent)
    : QWidget(parent),
      origin_edit_(new QPlainTextEdit),
      translate_edit_(new QPlainTextEdit),
      type_combobox_(new QComboBox),
      translate_btn_(new QPushButton),
      m_delayTimer(new QTimer),
      m_api(new YoudaoAPI)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    QHBoxLayout *translate_layout = new QHBoxLayout;

    translate_btn_->setFixedHeight(35);
    type_combobox_->setFixedHeight(35);

    translate_btn_->setText(tr("Translation"));
    type_combobox_->addItem(tr("Automatic detection"));
    type_combobox_->addItem(tr("Chinese to English"));
    type_combobox_->addItem(tr("Chinese to Japanese"));
    type_combobox_->addItem(tr("Chinese to Korean"));
    type_combobox_->addItem(tr("Chinese to French"));
    type_combobox_->addItem(tr("Chinese to Russian"));
    type_combobox_->addItem(tr("Chinese to Spanish"));
    type_combobox_->addItem(tr("English to Chinese"));

    translate_layout->addWidget(type_combobox_);
    translate_layout->addWidget(translate_btn_);

    layout->setContentsMargins(15, 10, 15, 15);
    layout->addWidget(origin_edit_);
    layout->addSpacing(5);
    layout->addLayout(translate_layout);
    layout->addSpacing(5);
    layout->addWidget(translate_edit_);

    // translate_btn_->setObjectName("QueryBtn");
    // translate_btn_->setStyleSheet(translate_btn_->styleSheet() + "border-radius: 4px");
    translate_btn_->setFixedSize(130, 35);

    origin_edit_->setPlaceholderText(tr("Please enter the text you want to translate"));
    translate_edit_->setReadOnly(true);

    m_delayTimer->setSingleShot(true);
    m_delayTimer->setInterval(500);

    connect(m_api, &YoudaoAPI::translateFinished, this, &TranslatePage::handleTranslateFinished);
    connect(translate_btn_, &QPushButton::clicked, this, &TranslatePage::translate);
    connect(type_combobox_, &QComboBox::currentTextChanged, [=] { translate(); });
    connect(m_delayTimer, &QTimer::timeout, this, &TranslatePage::translate);

    connect(origin_edit_, &QPlainTextEdit::textChanged, [=] {
        if (origin_edit_->toPlainText().isEmpty()) {
            translate_edit_->clear();
        }

        delayTranslate();
    });
}

TranslatePage::~TranslatePage()
{
}

void TranslatePage::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Return && (e->modifiers() & Qt::ControlModifier)) {
        translate();
    }
}

void TranslatePage::translate()
{
    QString text = origin_edit_->toPlainText();

    if (text.isEmpty())
        return;

    int currentType = type_combobox_->currentIndex();
    QString type;

    switch (currentType) {
    case 0:
        type = "AUTO";
        break;
    case 1:
        type = "ZH_CN2EN";
        break;
    case 2:
        type = "ZH_CN2JA";
        break;
    case 3:
        type = "ZH_CN2KR";
        break;
    case 4:
        type = "ZH_CN2FR";
        break;
    case 5:
        type = "ZH_CN2RU";
        break;
    case 6:
        type = "ZH_CN2SP";
        break;
    case 7:
        type = "EN2ZH_CN";
        break;
    default:
        break;
    }

    m_api->translate(text, type);
}

void TranslatePage::handleTranslateFinished(const QString &result)
{
    translate_edit_->setPlainText(result);
}

void TranslatePage::delayTranslate()
{
    m_delayTimer->start();
}
