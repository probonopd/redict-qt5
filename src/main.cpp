#include "mainwindow.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QTranslator>
#include <QFile>

inline QByteArray get_file_content(const QString &file_name)
{
    QFile file(file_name);

    if (file.open(QIODevice::ReadOnly)) {
        return file.readAll();
    }

    return QByteArray();
}

inline void move_to_center(QWidget *w)
{
    QDesktopWidget *dw = QApplication::desktop();
    QRect parent_rect = dw->availableGeometry(dw->primaryScreen());

    if (w->parentWidget()) {
        parent_rect = w->parentWidget()->geometry();
    }

    w->move(parent_rect.center() - w->rect().center());
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyleSheet(get_file_content(":/qss/style.qss"));

    QTranslator translator;
    if (translator.load(QString(":/translations/redict_%1.qm")
                        .arg(QLocale::system().name()))) {
        qApp->installTranslator(&translator);
    }

    MainWindow w;
    w.show();

    move_to_center(&w);

    return a.exec();
}
