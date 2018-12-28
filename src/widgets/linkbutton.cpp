#include "linkbutton.h"

LinkButton::LinkButton(const QString &text, QWidget *parent)
    : QPushButton(text, parent)
{
    setCursor(Qt::PointingHandCursor);
    setObjectName("LinkButton");
}
