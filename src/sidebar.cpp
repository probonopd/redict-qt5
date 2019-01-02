#include "sidebar.h"
#include "utils.h"
#include "sidebutton.h"
#include <QPainter>

SideBar::SideBar(QWidget *parent)
    : QWidget(parent),
      main_layout_(new QVBoxLayout(this)),
      button_group_(new QButtonGroup)
{
    main_layout_->setContentsMargins(0, 0, 2, 0);
    main_layout_->setSpacing(0);

    button_list_ << tr("Home") << tr("Translation")
                 << tr("Setttings") << tr("About");

    if (Utils::isChinese()) {
        button_list_.insert(3, tr("Donate"));
    }

    setObjectName("SideBar");
    setFixedWidth(150);
    initButtons();

    connect(button_group_,
            static_cast<void(QButtonGroup::*)(int)>(&QButtonGroup::buttonClicked),
            this, &SideBar::buttonClicked);
}

void SideBar::paintEvent(QPaintEvent *e)
{
    QWidget::paintEvent(e);

    QPainter painter(this);
    QRect right_path = rect();
    right_path.setLeft(rect().right() - 1);
    right_path.setWidth(1);
    painter.fillRect(right_path, QColor("#E6E6E6"));
}

void SideBar::initButtons()
{
    for (int i = 0; i < button_list_.size(); ++i) {
        QString name = button_list_.at(i);
        SideButton *btn = new SideButton;
        btn->setText(name);
        btn->setFixedHeight(BUTTON_ITEM_HEIGHT);
        btn->setFocusPolicy(Qt::NoFocus);
        btn->setCheckable(true);

        main_layout_->addWidget(btn);
        button_group_->addButton(btn, i);
    }

    button_group_->buttons().first()->setChecked(true);
    main_layout_->addStretch();
}
