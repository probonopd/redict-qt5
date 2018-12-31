#include "spinner.h"
#include <QPainter>
#include <QtMath>

Spinner::Spinner(QWidget *parent)
    : QWidget(parent),
      refresh_timer_(new QTimer)
{
    indicator_colors_ << createDefaultIndicatorColorList(QColor(200, 46, 255));
    indicator_colors_ << createDefaultIndicatorColorList(QColor(207, 225, 0));
    indicator_colors_ << createDefaultIndicatorColorList(QColor(0, 255, 241));

    refresh_timer_->setInterval(30);

    connect(refresh_timer_, &QTimer::timeout, this, [=] {
        current_degree_ += 14;
        update();
    });
}

void Spinner::start()
{
    refresh_timer_->start();
}

void Spinner::stop()
{
    refresh_timer_->stop();
}

void Spinner::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);

    auto degreeCurrent = current_degree_ * 1.0;
    auto center = QRectF(rect()).center();
    auto radius = qMin(rect().width(), rect().height()) / 2.0;
    auto indicatorRadius = radius / 2 / 2 * 1.1;
    auto indicatorDegreeDelta = 360 / indicator_colors_.count();

    for (int i = 0; i <  indicator_colors_.count(); ++i) {
        auto colors = indicator_colors_.value(i);
        for (int j = 0; j < colors.count(); ++j) {
            degreeCurrent = current_degree_ - j * indicator_shadow_offset_ + indicatorDegreeDelta * i;
            auto x = (radius - indicatorRadius) * qCos(qDegreesToRadians(degreeCurrent));
            auto y = (radius - indicatorRadius) * qSin(qDegreesToRadians(degreeCurrent));

            x = center.x() + x;
            y = center.y() + y;
            auto tl = QPointF(x - 1 * indicatorRadius, y - 1 * indicatorRadius);
            QRectF rf(tl.x(), tl.y(), indicatorRadius * 2, indicatorRadius * 2);

            QPainterPath path;
            path.addEllipse(rf);

            painter.fillPath(path, colors.value(j));
        }
    }
}

QList<QColor> Spinner::createDefaultIndicatorColorList(QColor color)
{
    QList<QColor> colors;
    QList<int> opacitys;
    opacitys << 100 << 30 << 15 << 10 << 5 << 4 << 3 << 2 << 1;
    for (int i = 0; i < opacitys.count(); ++i) {
        color.setAlpha(255 * opacitys.value(i) / 100);
        colors << color;
    }
    return colors;
}
