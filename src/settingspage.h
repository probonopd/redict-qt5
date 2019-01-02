#ifndef SETTINGSPAGE_H
#define SETTINGSPAGE_H

#include <QWidget>
#include <QCheckBox>
#include <QSettings>
#include "widgets/contentframe.h"

class SettingsPage : public ContentFrame
{
    Q_OBJECT

public:
    explicit SettingsPage(QWidget *parent = nullptr);

    void setOption(const QString &key, const QVariant &value);
    QVariant option(const QString &key);

signals:
    void trayStateChanged(bool enabled);

private:
    void initUI();
    void initSettings();

    void handleTrayStateChanged();

private:
    QSettings *settings_;
    QCheckBox *tray_check_box_;
};

#endif // SETTINGSPAGE_H
