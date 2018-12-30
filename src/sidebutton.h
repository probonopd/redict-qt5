#ifndef SIDEBUTTON_H
#define SIDEBUTTON_H

#include <QPushButton>

class SideButton : public QPushButton
{
    Q_OBJECT

public:
    explicit SideButton(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *) override;
};

#endif // SIDEBUTTON_H
