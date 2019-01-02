#include "mainwindow.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QTranslator>
#include <QFile>

#ifdef Q_OS_LINUX
#include <QDateTime>
#include <QFileInfo>
#include <QSettings>
#include <QDir>
#include <unistd.h>
#elif defined(Q_OS_WIN)
#include <windows.h>
#endif

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
    a.setOrganizationName("rekols");
    a.setApplicationName("redict");

#ifdef Q_OS_UNIX
    QSettings lock_file(QDir::homePath() + "/.redict/redict.pid", QSettings::IniFormat);
    QString last_pid = lock_file.value("LastStart/pid").toString();
    if (last_pid.length() && QDir("/proc/" + last_pid).exists() &&
        lock_file.value("LastStart/time").toDateTime() == QFileInfo("/proc/" + last_pid).created())
    {
        qWarning() << "redict already running";
        return 0;
    }
    lock_file.setValue("LastStart/pid", getpid());
    lock_file.setValue("LastStart/time", QFileInfo("/proc/" + QString::number(getpid())).created());
    lock_file.sync();
#elif defined(Q_OS_WIN)
    HANDLE hMutex = CreateMutex(NULL, true, (LPCTSTR)"redict");
    if (GetLastError() == ERROR_ALREADY_EXISTS) {
        return 0;
    }

    QFont font = a.font();
    font.setFamily("Microsoft Yahei");
    a.setFont(font);
#endif

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
