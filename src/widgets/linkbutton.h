#ifndef LINKBUTTON_H
#define LINKBUTTON_H

#include <QPushButton>

class LinkButton : public QPushButton
{
    Q_OBJECT

public:
    explicit LinkButton(const QString & text = QString(), QWidget *parent = nullptr);
};

#endif // LINKBUTTON_H
