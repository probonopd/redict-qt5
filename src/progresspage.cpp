#include "progresspage.h"
#include "widgets/linkbutton.h"
#include <QSvgWidget>
#include <QLabel>

ProgressPage::ProgressPage(QWidget *parent)
    : QWidget(parent),
      stacked_layout_(new QStackedLayout),
      spinner_(new Spinner)
{
    QWidget *spinner_widget = new QWidget;
    QVBoxLayout *spinner_layout = new QVBoxLayout(spinner_widget);
    spinner_->setFixedSize(40, 40);
    spinner_layout->addWidget(spinner_, 0, Qt::AlignCenter);

    QWidget *fail_widget = new QWidget;
    QVBoxLayout *fail_layout = new QVBoxLayout(fail_widget);
    QSvgWidget *network_icon = new QSvgWidget(":/images/network_error.svg");
    QLabel *tips_label = new QLabel(tr("Unable to access the network."));
    LinkButton *reload_button = new LinkButton(tr("Reload"));

    network_icon->setFixedSize(50, 50);

    fail_layout->addStretch();
    fail_layout->addWidget(network_icon, 0, Qt::AlignHCenter);
    fail_layout->addSpacing(10);
    fail_layout->addWidget(tips_label, 0, Qt::AlignHCenter);
    fail_layout->addWidget(reload_button, 0, Qt::AlignHCenter);
    fail_layout->addStretch();

    stacked_layout_->addWidget(spinner_widget);
    stacked_layout_->addWidget(fail_widget);
    setLayout(stacked_layout_);

    connect(reload_button, &LinkButton::clicked, this, &ProgressPage::reloadButtonClicked);
}

void ProgressPage::switchToProgress()
{
    spinner_->start();
    stacked_layout_->setCurrentIndex(0);
}

void ProgressPage::switchToError()
{
    spinner_->stop();
    stacked_layout_->setCurrentIndex(1);
}

void ProgressPage::stop()
{
    spinner_->stop();
}
