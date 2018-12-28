#include "translatepage.h"
#include "mainwindow.h"
#include <QVBoxLayout>
#include <QKeyEvent>

TranslatePage::TranslatePage(QWidget *parent)
    : QWidget(parent),
      origin_edit_(new QTextEdit),
      translate_edit_(new QTextEdit),
      type_combobox_(new QComboBox),
      translate_btn_(new QPushButton("翻译")),
      m_api(new YoudaoAPI)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    QHBoxLayout *translate_layout = new QHBoxLayout;

    type_combobox_->addItem("自动检测语言");
    type_combobox_->addItem("中文 → 英语");
    type_combobox_->addItem("中文 → 日语");
    type_combobox_->addItem("中文 → 韩语");
    type_combobox_->addItem("中文 → 法语");
    type_combobox_->addItem("中文 → 俄语");
    type_combobox_->addItem("中文 → 西班牙语");
    type_combobox_->addItem("英语 → 中文");

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

    origin_edit_->setPlaceholderText("请输入您要翻译的文字");
    translate_edit_->setReadOnly(true);

    connect(translate_btn_, &QPushButton::clicked, this, &TranslatePage::translate);
    connect(m_api, &YoudaoAPI::translateFinished, this, &TranslatePage::handleTranslateFinished);
    connect(type_combobox_, &QComboBox::currentTextChanged, [=] { translate(); });

    connect(origin_edit_, &QTextEdit::textChanged, [=] {
        if (origin_edit_->toPlainText().isEmpty()) {
            translate_edit_->clear();
        }
    });

//    connect(origin_edit_, &QTextEdit::focusIn, [=] { translate_edit_->clearSelection(); });
//    connect(origin_edit_, &QTextEdit::focusOut, [=] { origin_edit_->clearSelection(); });
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
