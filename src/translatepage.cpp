#include "translatepage.h"
#include "mainwindow.h"
#include <QVBoxLayout>
#include <QKeyEvent>

TranslatePage::TranslatePage(QWidget *parent)
    : QWidget(parent),
      m_orginEdit(new QTextEdit),
      m_transEdit(new QTextEdit),
      m_typeBox(new QComboBox),
      m_transBtn(new QPushButton("翻译")),
      m_api(new YoudaoAPI)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    QHBoxLayout *transLayout = new QHBoxLayout;

    m_typeBox->addItem("自动检测语言");
    m_typeBox->addItem("中文 → 英语");
    m_typeBox->addItem("中文 → 日语");
    m_typeBox->addItem("中文 → 韩语");
    m_typeBox->addItem("中文 → 法语");
    m_typeBox->addItem("中文 → 俄语");
    m_typeBox->addItem("中文 → 西班牙语");
    m_typeBox->addItem("英语 → 中文");

    transLayout->addWidget(m_typeBox);
    transLayout->addWidget(m_transBtn);

    layout->setContentsMargins(15, 10, 15, 15);
    layout->addWidget(m_orginEdit);
    layout->addSpacing(5);
    layout->addLayout(transLayout);
    layout->addSpacing(5);
    layout->addWidget(m_transEdit);

    // m_transBtn->setObjectName("QueryBtn");
    // m_transBtn->setStyleSheet(m_transBtn->styleSheet() + "border-radius: 4px");
    m_transBtn->setFixedSize(130, 35);

    m_orginEdit->setPlaceholderText("请输入您要翻译的文字");
    m_transEdit->setReadOnly(true);

    connect(m_transBtn, &QPushButton::clicked, this, &TranslatePage::translate);
    connect(m_api, &YoudaoAPI::translateFinished, this, &TranslatePage::handleTranslateFinished);
    connect(m_typeBox, &QComboBox::currentTextChanged, [=] { translate(); });

    connect(m_orginEdit, &QTextEdit::textChanged, [=] {
        if (m_orginEdit->toPlainText().isEmpty()) {
            m_transEdit->clear();
        }
    });

//    connect(m_orginEdit, &QTextEdit::focusIn, [=] { m_transEdit->clearSelection(); });
//    connect(m_orginEdit, &QTextEdit::focusOut, [=] { m_orginEdit->clearSelection(); });
}

TranslatePage::~TranslatePage()
{
}

void TranslatePage::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Return && (e->modifiers() & Qt::ControlModifier)) {
        translate();
    }

    // request window keypress.
//    (qobject_cast<MainWindow *>(this->window()))->requestKeyPressEvent(e);
}

void TranslatePage::translate()
{
    QString text = m_orginEdit->toPlainText();

    if (text.isEmpty())
        return;

    int currentType = m_typeBox->currentIndex();
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
    m_transEdit->setPlainText(result);
}
