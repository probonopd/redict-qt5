#include "mainwindow.h"
#include "sidebar.h"
#include "utils.h"

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
      settings_page_(new SettingsPage),
      donate_page_(new DonatePage),
      about_page_(new AboutPage),
      stacked_layout_(new QStackedLayout),
      float_dialog_(new FloatDialog),
      tray_icon_(new TrayIcon)
{
    initAttributes();
    initTesseractOCR();
    initTrayIcon();
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
    stacked_layout_->addWidget(settings_page_);

    if (Utils::isChinese()) {
        stacked_layout_->addWidget(donate_page_);
    }

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
    connect(settings_page_, &SettingsPage::trayStateChanged, this, &MainWindow::initTrayIcon);
    connect(tray_icon_, &TrayIcon::openActionTriggered, this, &MainWindow::toggleWindowVisible);
    connect(tray_icon_, &TrayIcon::exitActionTriggered, qApp, &QApplication::quit);
}

void MainWindow::initTesseractOCR()
{
#ifdef Q_OS_LINUX
    QTimer *timer = new QTimer(this);
    timer->setSingleShot(true);
    timer->setInterval(300);
    connect(timer, &QTimer::timeout, this, &MainWindow::detectPicture);

    connect(qApp->clipboard(), &QClipboard::dataChanged, this, [=] {
        screenshot_image_ = qApp->clipboard()->image(QClipboard::Clipboard);
        timer->start();
    });
#endif
}

void MainWindow::initTrayIcon()
{
    if (settings_page_->option("tray_icon").toBool()) {
        tray_icon_->show();
    } else {
        // Ubuntu 18.10 is invalid !!!
        tray_icon_->hide();
    }
}

void MainWindow::detectPicture()
{
#ifdef Q_OS_LINUX
    QImage image = screenshot_image_;
    if (image.isNull()) {
        return;
    }

    QSettings settings;
    QString image_path = QString("%1/redict_ocr.png")
            .arg(QFileInfo(settings.fileName()).absolutePath());

    QString text_path = QString("%1/redict_ocr")
            .arg(QFileInfo(settings.fileName()).absolutePath());

    image = image.scaled(QSize(image.width() * 3, image.height() * 3), Qt::KeepAspectRatio);
    image.save(image_path, "PNG");

    QProcess process;
    process.start("tesseract", QStringList() << image_path << text_path << "-l" << "eng");
    process.waitForFinished(-1);

    QFile file(text_path + ".txt");
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
    file.close();
#endif
}

void MainWindow::toggleWindowVisible()
{
    if (isVisible()) {
        QMainWindow::setVisible(false);
    } else {
        QMainWindow::setVisible(true);
        QMainWindow::activateWindow();
    }
}

void MainWindow::handleSideButtonClicked(int index)
{
    stacked_layout_->setCurrentIndex(index);
}

void MainWindow::closeEvent(QCloseEvent *e)
{
    if (settings_page_->option("tray_icon").toBool()) {
        QMainWindow::setVisible(false);
        e->ignore();
    } else {
        float_dialog_->close();
        e->accept();
    }
}
