#include "contentframe.h"
#include <QScrollArea>

ContentFrame::ContentFrame(QWidget *parent)
    : QWidget(parent),
      content_widget_(new QWidget),
      content_layout_(new QVBoxLayout),
      scroll_area_(new QScrollArea)
{
    QVBoxLayout *layout = new QVBoxLayout;

    content_widget_->setLayout(content_layout_);

    scroll_area_->setFrameStyle(QFrame::NoFrame);
    scroll_area_->setWidget(content_widget_);
    scroll_area_->setWidgetResizable(true);
    scroll_area_->setContentsMargins(0, 0, 0, 0);

    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(scroll_area_);

    setLayout(layout);
}

void ContentFrame::addSpacing(int size)
{
    content_layout_->addSpacing(size);
}

void ContentFrame::addStretch(int stretch)
{
    content_layout_->addStretch(stretch);
}

void ContentFrame::addWidget(QWidget *w, int stretch, Qt::Alignment alignment)
{
    content_layout_->addWidget(w, stretch, alignment);
}

void ContentFrame::addLayout(QLayout *layout, int stretch)
{
    content_layout_->addLayout(layout, stretch);
}
