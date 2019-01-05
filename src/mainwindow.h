#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "homepage.h"
#include "translatepage.h"
#include "settingspage.h"
#include "donatepage.h"
#include "aboutpage.h"
#include "widgets/floatdialog.h"
#include "widgets/trayicon.h"

class SideBar;
class QStackedLayout;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void initAttributes();
    void initTesseractOCR();
    void initTrayIcon();

    void detectPicture();

    void toggleWindowVisible();
    void handleSideButtonClicked(int);

protected:
    void closeEvent(QCloseEvent *) override;

private:
    SideBar *side_bar_;
    HomePage *home_page_;
    TranslatePage *translate_page_;
    SettingsPage *settings_page_;
    DonatePage *donate_page_;
    AboutPage *about_page_;
    QStackedLayout *stacked_layout_;
    FloatDialog *float_dialog_;
    TrayIcon *tray_icon_;

    QImage screenshot_image_;
};

#endif // MAINWINDOW_H
