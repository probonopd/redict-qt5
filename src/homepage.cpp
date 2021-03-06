#include "homepage.h"
#include <QVBoxLayout>
#include <QTimer>

HomePage::HomePage(QWidget *parent)
    : QWidget(parent),
      query_edit_(new QLineEdit),
      stacked_layout_(new QStackedLayout),
      daily_page_(new DailyPage),
      dict_page_(new DictPage)
{
    QVBoxLayout *main_layout = new QVBoxLayout;

    stacked_layout_->addWidget(daily_page_);
    stacked_layout_->addWidget(dict_page_);

    query_edit_->setPlaceholderText(tr("Enter the word or phrase you want to query"));
    query_edit_->setFocusPolicy(Qt::StrongFocus);
    query_edit_->setFixedHeight(40);

    main_layout->setMargin(0);
    main_layout->setSpacing(0);
    main_layout->addWidget(query_edit_);
    main_layout->addSpacing(5);
    main_layout->addLayout(stacked_layout_);
    setLayout(main_layout);

    connect(query_edit_, &QLineEdit::textEdited, this, &HomePage::handleTextEdited);
    connect(query_edit_, &QLineEdit::returnPressed, this, &HomePage::handleEditReturnPressed);
}

void HomePage::handleTextEdited()
{
    if (query_edit_->text().isEmpty()) {
        stacked_layout_->setCurrentIndex(0);
    } else {
        dict_page_->queryWord(query_edit_->text());
        stacked_layout_->setCurrentIndex(1);
    }
}

void HomePage::handleEditReturnPressed()
{
    query_edit_->selectAll();
    handleTextEdited();
}

