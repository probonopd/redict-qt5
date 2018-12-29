#include "sidebutton.h"
#include <QPainter>

SideButton::SideButton(QWidget *parent)
    : QPushButton(parent)
{
    setObjectName("SideButton");
}

void SideButton::paintEvent(QPaintEvent *e)
{
    QPushButton::paintEvent(e);

    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform);

    if (!isChecked()) {
        return;
    }

    QRect sep_path = rect();
    sep_path.setLeft(0);
    sep_path.setWidth(4);
    painter.fillRect(sep_path, QColor(66, 133, 244));
}
