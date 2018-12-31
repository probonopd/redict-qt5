#ifndef SPINNER_H
#define SPINNER_H

#include <QWidget>
#include <QTimer>

class Spinner : public QWidget
{
    Q_OBJECT

public:
    explicit Spinner(QWidget *parent = nullptr);

    void start();
    void stop();

protected:
    void paintEvent(QPaintEvent *);

private:
    QList<QColor> createDefaultIndicatorColorList(QColor color);

private:
    QTimer *refresh_timer_;
    double indicator_shadow_offset_ = 10;
    double current_degree_ = 0.0;

    QList<QList<QColor>> indicator_colors_;
};

#endif // SPINNER_H
