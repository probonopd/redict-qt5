#ifndef DICTPAGE_H
#define DICTPAGE_H

#include <QWidget>
#include <QLabel>
#include "youdaoapi.h"

class QVBoxLayout;
class DictPage : public QWidget
{
    Q_OBJECT

public:
    explicit DictPage(QWidget *parent = nullptr);

    void queryWord(const QString &text);
    void setFrameMargins(int, int, int, int);

private:
    void queryWordFinished(std::tuple<QString, QString, QString, QString, QString>);

private:
    YoudaoAPI *youdao_api_;
    QLabel *word_label_;
    QLabel *explains_label_;
    QVBoxLayout *frame_layout_;
};

#endif // DICTPAGE_H
