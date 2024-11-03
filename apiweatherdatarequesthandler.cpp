#include "apiweatherdatarequesthandler.h"

#include <QDebug>

ApiWeatherDataRequestHandler::ApiWeatherDataRequestHandler(QObject *parent):
    QObject(parent),
    manager(new QNetworkAccessManager(this)),
    updateTimer(new QTimer(this)),
    updateIntervalSeconds(0)
{
    connect(updateTimer, &QTimer::timeout, this, [this]{
        makeRequest(lastUrl, lastParams, updateIntervalSeconds);
    });
}

void ApiWeatherDataRequestHandler::makeRequest(const QString &url, const QMap<QString, QString> &params, int updateInterval)
{
    lastUrl = url;
    lastParams = params;
    updateIntervalSeconds = updateInterval;

    if (updateIntervalSeconds > 0) {
        updateTimer->start(updateIntervalSeconds * 1000);
    } else {
        updateTimer->stop();
    }

    QUrl qUrl(url);
    QUrlQuery query;

    for ( QMap<QString, QString>::const_iterator it = params.cbegin(); it != params.cend(); ++it) {
        query.addQueryItem(it.key(), it.value());
    }
    qUrl.setQuery(query);

    QNetworkRequest request(qUrl);
    QNetworkReply * reply = manager->get(request);

    lastRequestTime = QDateTime::currentDateTime();

    connect(reply, &QNetworkReply::finished, this, &ApiWeatherDataRequestHandler::handleReply);
}

void ApiWeatherDataRequestHandler::handleReply()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());

    if (reply)
    {
        if (reply->error() == QNetworkReply::NoError)
        {
            QString response = reply->readAll();
            emit requestSucceeded(response);
        }
        else{
            emit requestFailed(reply->errorString());
        }
        reply->deleteLater();
    }
}

