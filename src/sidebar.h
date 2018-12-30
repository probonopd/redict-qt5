#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <QWidget>
#include <QVBoxLayout>
#include <QButtonGroup>

#define BUTTON_ITEM_HEIGHT 35

class SideBar : public QWidget
{
    Q_OBJECT

public:
    explicit SideBar(QWidget *parent = nullptr);

signals:
    void buttonClicked(int);

protected:
    void paintEvent(QPaintEvent *) override;

private:
    void initButtons();

private:
    QVBoxLayout *main_layout_;
    QButtonGroup *button_group_;
    QStringList button_list_;
};

#endif // SIDEBAR_H
