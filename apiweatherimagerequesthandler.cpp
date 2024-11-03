#include "apiweatherimagerequesthandler.h"

ApiWeatherImageRequestHandler::ApiWeatherImageRequestHandler(QObject *parent)
    : QObject{parent},
    manager(new QNetworkAccessManager(this))
{}

void ApiWeatherImageRequestHandler::handleReply()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());

    if (reply)
    {
        if (reply->error() == QNetworkReply::NoError)
        {
            QImageReader imageReader(reply);
            QImage response = imageReader.read();
            if (response.isNull())
            {
                emit requestFailed(imageReader.errorString());
            }
            emit requestSucceeded(response);
        }
        else{
            emit requestFailed(reply->errorString());
        }
        reply->deleteLater();
    }
}

void ApiWeatherImageRequestHandler::makeRequest(const QString &code)
{
    QUrl qUrl(ApiWeatherImageRequestHandler::UrlImage.replace("CODE", code));
    QUrlQuery query;
    qUrl.setQuery(query);

    QNetworkRequest request(qUrl);
    QNetworkReply * reply = manager->get(request);

    connect(reply, &QNetworkReply::finished, this, &ApiWeatherImageRequestHandler::handleReply);
}
