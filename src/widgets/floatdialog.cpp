#include "floatdialog.h"
#include <QVBoxLayout>
#include <QKeyEvent>
#include <QDebug>

FloatDialog::FloatDialog(QWidget *parent)
    : QWidget(parent),
      dict_page_(new DictPage)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(dict_page_);
    layout->setMargin(0);

    dict_page_->setFrameMargins(10, 10, 10, 10);

    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Tool);
    setFocusPolicy(Qt::ClickFocus);
    setFixedSize(270, 300);

    QWidget::hide();
}

void FloatDialog::popup(const QPoint &pos)
{
    QWidget::move(QPoint(pos.x(), pos.y()));
    QWidget::show();
    QWidget::setFocus();
}

void FloatDialog::query(const QString &text)
{
    dict_page_->queryWord(text);
}

void FloatDialog::keyPressEvent(QKeyEvent *e)
{
    QWidget::keyPressEvent(e);

    switch (e->key()) {
    case Qt::Key_Escape:
        QWidget::hide();
        break;
    default:
        break;
    }
}
