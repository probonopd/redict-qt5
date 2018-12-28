#include "mainwindow.h"
#include "sidebar.h"
#include <QHBoxLayout>
#include <QStackedLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      side_bar_(new SideBar),
      home_page_(new HomePage),
      translate_page_(new TranslatePage),
      about_page_(new AboutPage),
      stacked_layout_(new QStackedLayout)
{
    initAttributes();
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
    stacked_layout_->addWidget(about_page_);

    main_layout->setMargin(0);
    main_layout->setSpacing(0);
    main_layout->addWidget(side_bar_);
    main_layout->addLayout(content_layout);
    main_widget->setLayout(main_layout);

    setCentralWidget(main_widget);
    setWindowIcon(QIcon(":/images/redict.svg"));
    setWindowTitle("Redict");
    setMinimumSize(700, 450);
    resize(700, 450);

    connect(side_bar_, &SideBar::buttonClicked, this, &MainWindow::handleSideButtonClicked);
}

void MainWindow::handleSideButtonClicked(int index)
{
    stacked_layout_->setCurrentIndex(index);
}
