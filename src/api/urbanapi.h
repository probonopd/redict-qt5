#ifndef URBANAPI_H
#define URBANAPI_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

class UrbanAPI : public QObject
{
    Q_OBJECT

public:
    UrbanAPI(QObject *parent = nullptr);

    void queryWordOfTheToday();

signals:
    void queryWordOfTheTodayFinished(QString, QString, QString);

private:
    void handlWordOfTheTodayFinished();

private:
    QNetworkAccessManager *access_manager_;
};

#endif // URBANAPI_H
