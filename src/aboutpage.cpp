#include "aboutpage.h"
#include "widgets/linkbutton.h"
#include <QDesktopServices>
#include <QVBoxLayout>
#include <QSvgWidget>
#include <QLabel>
#include <QUrl>

AboutPage::AboutPage(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *main_layout = new QVBoxLayout;
    setLayout(main_layout);

    QSvgWidget *icon_widget = new QSvgWidget(":/images/redict.svg");
    icon_widget->setFixedSize(120, 120);

    QLabel *title_label = new QLabel;
    title_label->setText("Redict");

    QLabel *version_label = new QLabel;
    version_label->setText(tr("Version") + ": 1.0");

    QLabel *copyright_label = new QLabel;
    copyright_label->setText(QStringLiteral("Copyright © 2019 Unson Wong(Rekols)"));

    QLabel *license_label = new QLabel;
    license_label->setText(tr("This project is licensed under version 3 of the GNU General Public License."));

    LinkButton *link_button = new LinkButton("https://github.com/rekols/redict-qt5");

    main_layout->setMargin(0);
    main_layout->addSpacing(50);
    main_layout->addWidget(icon_widget, 0, Qt::AlignHCenter);
    main_layout->addSpacing(5);
    main_layout->addWidget(title_label, 0, Qt::AlignHCenter);
    main_layout->addWidget(version_label, 0, Qt::AlignHCenter);
    main_layout->addWidget(link_button, 0, Qt::AlignHCenter);
    main_layout->addWidget(copyright_label, 0, Qt::AlignHCenter);
    main_layout->addWidget(license_label, 0, Qt::AlignHCenter);
    main_layout->addStretch();

    connect(link_button, &LinkButton::clicked, this, [=] {
        QDesktopServices::openUrl(QUrl(link_button->text()));
    });
}
