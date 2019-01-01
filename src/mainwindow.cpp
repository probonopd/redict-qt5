#include "mainwindow.h"
#include "sidebar.h"
#include <QHBoxLayout>
#include <QStackedLayout>
#include <QApplication>
#include <QClipboard>
#include <QProcess>
#include <QDir>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      side_bar_(new SideBar),
      home_page_(new HomePage),
      translate_page_(new TranslatePage),
      donate_page_(new DonatePage),
      about_page_(new AboutPage),
      stacked_layout_(new QStackedLayout),
      float_dialog_(new FloatDialog)
{
    initAttributes();
    // initTesseractOCR();
}

MainWindow::~MainWindow()
{

}

void MainWindow::initAttributes()
{
    QWidget *main_widget = new QWidget;
    QHBoxLayout *main_layout = new QHBoxLayout;

    QVBoxLayout *content_layout = new QVBoxLayout;
    content_layout->addLayout(stacked_layout_);

    stacked_layout_->addWidget(home_page_);
    stacked_layout_->addWidget(translate_page_);
    stacked_layout_->addWidget(donate_page_);
    stacked_layout_->addWidget(about_page_);

    main_layout->setMargin(0);
    main_layout->setSpacing(0);
    main_layout->addWidget(side_bar_);
    main_layout->addLayout(content_layout);
    main_widget->setLayout(main_layout);

    setCentralWidget(main_widget);
    setWindowIcon(QIcon(":/images/redict.svg"));
    setWindowTitle("Redict");
    setFixedSize(705, 455);

    connect(side_bar_, &SideBar::buttonClicked, this, &MainWindow::handleSideButtonClicked);
}

void MainWindow::initTesseractOCR()
{
#ifdef Q_OS_LINUX
    connect(qApp->clipboard(), &QClipboard::dataChanged, this, [=] {
        QImage image = qApp->clipboard()->image(QClipboard::Clipboard);
        if (image.isNull()) {
            return;
        }

        QString imgPath = QDir::homePath() + "/.local/redict_ocr.png";
        QString textPath = QDir::homePath() + "/.local/redict_ocr";
        image = image.scaled(QSize(image.width() * 2, image.height() * 2));
        image.save(imgPath, "PNG");

        QStringList support_languages = {"eng", "chi_sim", "chi_tra"};

        for (const QString &language : support_languages) {
            QProcess process;
            process.start("tesseract", QStringList() << imgPath << textPath << "-l" << language);
            process.waitForFinished(-1);

            QFile file(textPath + ".txt");
            if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                QString text = file.readAll();

                qDebug() << text.simplified();

                if (text.simplified().isEmpty()) {
                    float_dialog_->hide();
                    return;
                }

                if (float_dialog_->isVisible())
                    return;

                float_dialog_->query(text);
                float_dialog_->popup(QCursor::pos());
            }
        }
    });
#endif
}

void MainWindow::handleSideButtonClicked(int index)
{
    stacked_layout_->setCurrentIndex(index);
}
