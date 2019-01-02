#include "urbanapi.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

UrbanAPI::UrbanAPI(QObject *parent)
    : QObject(parent),
      access_manager_(new QNetworkAccessManager)
{
}

void UrbanAPI::queryText(const QString &text)
{
    QUrl url("http://api.urbandictionary.com/v0/define?term=" + text);
    QNetworkRequest request(url);
    QNetworkReply *reply = access_manager_->get(request);

    connect(reply, &QNetworkReply::finished, this, &UrbanAPI::handleQueryTextFinished);
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

void UrbanAPI::handleQueryTextFinished()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());

    if (reply->error() != QNetworkReply::NoError) {
        return;
    }

    QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
    QJsonArray list_obj = document.object().value("list").toArray();
    QString definition;
    QString example;
    QString word;
    QString author;
    QString datetime;

    if (list_obj.size() > 0) {
        QJsonObject obj = list_obj.first().toObject();
        definition = obj.value("definition").toString();
        example = obj.value("example").toString();
        word = obj.value("word").toString();
        author = obj.value("author").toString();
        datetime = obj.value("written_on").toString();
    }

    qDebug() << definition;

    emit queryTextFinished(word, definition, example, author, datetime);
}
