#ifndef CONTENTFRAME_H
#define CONTENTFRAME_H

#include <QWidget>
#include <QScrollArea>
#include <QVBoxLayout>

class ContentFrame : public QWidget
{
    Q_OBJECT

public:
    explicit ContentFrame(QWidget *parent = nullptr);

    void addSpacing(int size);
    void addStretch(int stretch = 0);
    void addWidget(QWidget *, int stretch = 0, Qt::Alignment alignment = Qt::Alignment());
    void addLayout(QLayout *layout, int stretch = 0);
    void setContentsMargins(int left, int top, int right, int bottom);

private:
    QWidget *content_widget_;
    QVBoxLayout *content_layout_;
    QScrollArea *scroll_area_;
};

#endif // CONTENTFRAME_H
