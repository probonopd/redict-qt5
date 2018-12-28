#ifndef DICTPAGE_H
#define DICTPAGE_H

#include <QWidget>
#include <QLabel>
#include "youdaoapi.h"

class DictPage : public QWidget
{
    Q_OBJECT

public:
    explicit DictPage(QWidget *parent = nullptr);

    void queryWord(const QString &text);

private:
    void queryWordFinished(std::tuple<QString, QString, QString, QString, QString>);

private:
    YoudaoAPI *youdao_api_;
    QLabel *word_label_;
    QLabel *explains_label_;
    QLabel *references_label_;
};

#endif // DICTPAGE_H
