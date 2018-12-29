#include "donatepage.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QGraphicsDropShadowEffect>

DonatePage::DonatePage(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    QLabel *label = new QLabel;
    label->setText(tr("Welcome to donate to me"));
    label->setStyleSheet("QLabel { font-size: 22px; }");

    QLabel *alipay_label = new QLabel;
    QPixmap pixmap(":/images/alipay.png");
    pixmap = pixmap.scaled(QSize(300, 400),
                           Qt::IgnoreAspectRatio,
                           Qt::SmoothTransformation);
    alipay_label->setPixmap(pixmap);
    alipay_label->setFixedSize(300, 400);

//    QGraphicsDropShadowEffect *img_shadow = new QGraphicsDropShadowEffect;
//    img_shadow->setBlurRadius(5);
//    img_shadow->setOffset(0, 0);
//    img_shadow->setColor(QColor(0, 0, 0, 255 * 0.5));
//    alipay_label->setGraphicsEffect(img_shadow);

    layout->setContentsMargins(20, 0, 0, 0);
    layout->setSpacing(0);
    layout->addSpacing(10);
    layout->addWidget(label, 0, Qt::AlignLeft);
    layout->addSpacing(10);
    layout->addWidget(alipay_label, 0, Qt::AlignLeft);
    layout->addStretch();
}
