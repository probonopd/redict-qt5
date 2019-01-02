#include "urbandictwidget.h"
#include <QDebug>

UrbanDictWidget::UrbanDictWidget(QWidget *parent)
    : ContentFrame(parent),
      define_label_(new QLabel),
      urban_api_(new UrbanAPI)
{
    define_label_->setTextInteractionFlags(Qt::TextSelectableByMouse);
    define_label_->setWordWrap(true);

    addWidget(define_label_);
    addStretch();

    setContentsMargins(30, 20, 30, 30);

    connect(urban_api_, &UrbanAPI::queryTextFinished, this, &UrbanDictWidget::handleQueryTextFinished);
}

void UrbanDictWidget::queryText(const QString &text)
{
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
}
