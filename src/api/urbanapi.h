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

    void queryText(const QString &text);
    void queryWordOfTheToday();

signals:
    void queryWordOfTheTodayFinished(QString, QString, QString);

    // word, definition, example, author, datetime
    void queryTextFinished(QString, QString, QString, QString, QString);

private:
    void handlWordOfTheTodayFinished();
    void handleQueryTextFinished();

private:
    QNetworkAccessManager *access_manager_;
};

#endif // URBANAPI_H
