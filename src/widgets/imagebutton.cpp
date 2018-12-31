#include "imagebutton.h"
#include <QApplication>
#include <QImageReader>
#include <QMouseEvent>
#include <QEvent>
#include <QIcon>
#include <QDebug>

ImageButton::ImageButton(QWidget *parent)
    : QLabel(parent)
{
    updateIcon();
}

ImageButton::ImageButton(const QString &normalPic, const QString &hoverPic,
                         const QString &pressPic, QWidget *parent)
    : QLabel(parent),
      state_(ImageButton::Normal),
      normal_pic_(normalPic),
      hover_pic_(hoverPic),
      press_pic_(pressPic)
{
    updateIcon();
}

void ImageButton::updateIcon()
{
    switch (state_) {
    case ImageButton::Hover:
        if (!hover_pic_.isEmpty()) {
            setPixmap(loadPixmap(hover_pic_));
        }
        break;
    case ImageButton::Press:
        if (!press_pic_.isEmpty()) {
            setPixmap(loadPixmap(press_pic_));
        }
        break;
    case ImageButton::Normal:
        if (!normal_pic_.isEmpty()) {
            setPixmap(loadPixmap(normal_pic_));
        }
        break;
    }

    setAlignment(Qt::AlignCenter);
}

void ImageButton::setState(ImageButton::State state)
{
    if (state_ == state)
        return;

    state_ = state;
    updateIcon();
}

QPixmap ImageButton::loadPixmap(const QString &path)
{
    qreal ratio = 1.0;

    const qreal devicePixelRatio = devicePixelRatioF();

    QPixmap pixmap;

    if (!qFuzzyCompare(ratio, devicePixelRatio)) {
        QImageReader reader;
        reader.setFileName(qt_findAtNxFile(path, devicePixelRatio, &ratio));
        if (reader.canRead()) {
            reader.setScaledSize(reader.size() * (devicePixelRatio / ratio));
            pixmap = QPixmap::fromImage(reader.read());
            pixmap.setDevicePixelRatio(devicePixelRatio);
        }
    } else {
        pixmap.load(path);
    }

    return pixmap;
}

void ImageButton::enterEvent(QEvent *e)
{
    setCursor(Qt::PointingHandCursor);

    setState(ImageButton::Hover);
    e->accept();
}

void ImageButton::leaveEvent(QEvent *e)
{
    setState(ImageButton::Normal);
    e->accept();
}

void ImageButton::mouseMoveEvent(QMouseEvent *e)
{
    if (!rect().contains(e->pos())) {
        setState(ImageButton::Normal);
    }
}

void ImageButton::mousePressEvent(QMouseEvent *e)
{
    if (e->button() != Qt::LeftButton) {
        return;
    }

    setState(ImageButton::Press);
    e->accept();
}

void ImageButton::mouseReleaseEvent(QMouseEvent *e)
{
    e->accept();

    if (e->button() != Qt::LeftButton) {
        return;
    }

    setState(ImageButton::Hover);

    emit clicked();
}
