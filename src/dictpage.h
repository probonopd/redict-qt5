#ifndef DICTPAGE_H
#define DICTPAGE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QMediaPlayer>
#include <QLabel>
#include "widgets/imagebutton.h"
#include "youdaoapi.h"

class DictPage : public QWidget
{
    Q_OBJECT

public:
    explicit DictPage(QWidget *parent = nullptr);

    void queryWord(const QString &text);
    void setFrameMargins(int, int, int, int);

private:
    void queryWordFinished(std::tuple<QString, QString, QString, QString, QString>);
    void playUSVoice();
    void playUKVoice();

private:
    YoudaoAPI *youdao_api_;
    QLabel *word_label_;
    QLabel *explains_label_;
    QVBoxLayout *frame_layout_;

    ImageButton *us_voice_btn_;
    ImageButton *uk_voice_btn_;

    QLabel *us_voice_label_;
    QLabel *uk_voice_label_;

    QMediaPlayer *voice_player_;

    QScrollArea *frame_;
};

#endif // DICTPAGE_H
