#include "sidebutton.h"
#include <QPainter>

SideButton::SideButton(QWidget *parent)
    : QPushButton(parent)
{
    setObjectName("SideButton");
    setStyleSheet("#SideButton {"
                  "margin: 0;"
                  "text-align: left;"
                  "padding: 5px 15px;"
                  "border: none;"
                  "}"
                  "#SideButton:hover {"
                  "background-color: rgb(237, 237, 237);"
                  "}"
                  "#SideButton:checked {"
                  "color: rgba(50, 115, 220);"
                  "font-weight: 500;"
                  "background-color: rgba(50, 115, 220, 0.1);"
                  "border: 1px solid rgba(50, 115, 220, 0.1);"
                  "border-left: none;"
                  "border-right: 5px;"
                  "}");
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
    painter.fillRect(sep_path, QColor(50, 115, 220));
}
