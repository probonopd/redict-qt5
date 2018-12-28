#ifndef YOUDAOAPI_H
#define YOUDAOAPI_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

class YoudaoAPI : public QObject
{
    Q_OBJECT

public:
    static YoudaoAPI *instance();

    YoudaoAPI(QObject *parent = nullptr);
    ~YoudaoAPI();

    void queryWord(const QString &text);
    void suggest(const QString &text);
    void translate(const QString &text, const QString &type);
    void loadImage(const QString &image_url);
    void queryDaily();

signals:
    // 0. query word
    // 1. UK phonetic
    // 2. US phonetic
    // 3. basic explains
    // 4. web references
    void searchFinished(std::tuple<QString, QString, QString, QString, QString>);

    // 0. title
    // 1. summary
    // 2. time
    // 3. voice url
    // 4. image url
    void dailyFinished(std::tuple<QString, QString, QString, QString, QString>);

    void translateFinished(const QString result);
    void suggestFinished(const QStringList list);
    void loadImageFinsihed(const QByteArray &data);

    void queryWordNetworkError();
    void dailyNetworkError();

private slots:
    void handleQueryWordFinished();
    void handleQueryDailyFinished();
    void handleTranslateFinished();
    void handleSuggestFinished();
    void handleLoadImageFinished();

private:
    QNetworkAccessManager *access_manager_;
};

#endif
