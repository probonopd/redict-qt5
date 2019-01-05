#include "floatdialog.h"
#include <QVBoxLayout>
#include <QKeyEvent>
#include <QDebug>

#ifdef Q_OS_LINUX
#include "../linux/eventmonitor.h"
#endif

FloatDialog::FloatDialog(QWidget *parent)
    : QWidget(parent),
      dict_page_(new DictPage)
{
#ifdef Q_OS_LINUX
    event_monitor_ = new EventMonitor;
    connect(event_monitor_, &EventMonitor::buttonPress, this, &FloatDialog::onGlobMousePress, Qt::QueuedConnection);
    event_monitor_->start();
#endif

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(dict_page_);
    layout->setMargin(0);

    dict_page_->setFrameMargins(10, 10, 10, 10);

    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Tool);
    setFocusPolicy(Qt::ClickFocus);
    setFixedSize(320, 300);

    QWidget::hide();
}

void FloatDialog::popup(const QPoint &pos)
{
    QWidget::move(QPoint(pos.x(), pos.y()));
    QWidget::show();
    QWidget::setFocus();

#ifdef Q_OS_LINUX
    if (!event_monitor_->isRunning()) {
        event_monitor_->start();
    }
#endif
}

void FloatDialog::onGlobMousePress(const int &x, const int &y)
{
    QPoint mouse_pos(x, y);

    if (isVisible()) {
        const QRect rect = QRect(pos(), size());
        if (rect.contains(mouse_pos))
            return;
    }

    const QRect rect = QRect(pos(), size());
    if (rect.contains(mouse_pos))
        return;

#ifdef Q_OS_LINUX
    if (event_monitor_->isRunning()) {
        event_monitor_->quit();
    }
#endif

    QWidget::hide();
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
