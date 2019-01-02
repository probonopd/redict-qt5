#include "settingspage.h"
#include <QDebug>

SettingsPage::SettingsPage(QWidget *parent)
    : ContentFrame(parent),
      settings_(new QSettings(this)),
      tray_check_box_(new QCheckBox)
{
    initUI();
    initSettings();
}

void SettingsPage::setOption(const QString &key, const QVariant &value)
{
    settings_->setValue(key, value);
}

QVariant SettingsPage::option(const QString &key)
{
    return settings_->value(key);
}

void SettingsPage::initUI()
{
    tray_check_box_->setText(tr("Turn on the system tray icon"));

    connect(tray_check_box_, &QCheckBox::stateChanged, this, &SettingsPage::handleTrayStateChanged);

    addWidget(tray_check_box_);
    addStretch();
}

void SettingsPage::initSettings()
{
    bool enable_tray_icon = settings_->value("tray_icon", false).toBool();

    tray_check_box_->setChecked(enable_tray_icon);
}

void SettingsPage::handleTrayStateChanged()
{
    bool enabled = tray_check_box_->isChecked();

    settings_->setValue("tray_icon", enabled);

    emit trayStateChanged(enabled);
}
