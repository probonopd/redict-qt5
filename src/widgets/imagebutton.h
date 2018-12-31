#ifndef IMAGEBUTTON_H
#define IMAGEBUTTON_H

#include <QLabel>

class ImageButton : public QLabel
{
    Q_OBJECT

public:
    enum State {
        Normal,
        Hover,
        Press
    };

    ImageButton(QWidget *parent = nullptr);
    ImageButton(const QString &normalPic, const QString &hoverPic,
                const QString &pressPic, QWidget *parent = nullptr);

signals:
    void clicked();

private:
    void updateIcon();
    void setState(ImageButton::State state);
    QPixmap loadPixmap(const QString &path);

protected:
    void enterEvent(QEvent *e) override;
    void leaveEvent(QEvent *e) override;
    void mouseMoveEvent(QMouseEvent *e) override;
    void mousePressEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;

private:
    State state_;
    QString normal_pic_;
    QString hover_pic_;
    QString press_pic_;
};

#endif // IMAGEBUTTON_H
