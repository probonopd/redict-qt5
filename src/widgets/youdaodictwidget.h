#ifndef YOUDAODICTWIDGET_H
#define YOUDAODICTWIDGET_H

#include "contentframe.h"
#include "imagebutton.h"
#include "../youdaoapi.h"

#include <QMediaPlayer>
#include <QLabel>

class YoudaoDictWidget : public ContentFrame
{
    Q_OBJECT

public:
    explicit YoudaoDictWidget(QWidget *parent = nullptr);

    void queryWord(const QString &text);

private:
    void queryWordFinished(std::tuple<QString, QString, QString, QString, QString>);
    void playUSVoice();
    void playUKVoice();

private:
    YoudaoAPI *youdao_api_;
    QLabel *word_label_;
    QLabel *explains_label_;

    ImageButton *us_voice_btn_;
    ImageButton *uk_voice_btn_;

    QLabel *us_voice_label_;
    QLabel *uk_voice_label_;

    QMediaPlayer *voice_player_;
};

#endif // YOUDAODICTWIDGET_H
