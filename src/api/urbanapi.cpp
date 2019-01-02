#include "urbanapi.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

UrbanAPI::UrbanAPI(QObject *parent)
    : QObject(parent),
      access_manager_(new QNetworkAccessManager)
{
    queryWordOfTheToday();
}

void UrbanAPI::queryWordOfTheToday()
{
    QUrl url("http://urban-word-of-the-day.herokuapp.com");
    QNetworkRequest request(url);
    QNetworkReply *reply = access_manager_->get(request);

    connect(reply, &QNetworkReply::finished, this, &UrbanAPI::handlWordOfTheTodayFinished);
}

void UrbanAPI::handlWordOfTheTodayFinished()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());

    if (reply->error() != QNetworkReply::NoError) {
        return;
    }

    QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
    QString word = document.object().value("word").toString().remove('\n');
    QString meaning = document.object().value("meaning").toString().remove('\n');
    QString example = document.object().value("example").toString().remove('\n');

    emit queryWordOfTheTodayFinished(word, meaning, example);
}
