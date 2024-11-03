#ifndef APIWEATHERIMAGEREQUESTHANDLER_H
#define APIWEATHERIMAGEREQUESTHANDLER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QUrlQuery>
#include <QImage>
#include <QImageReader>

class ApiWeatherImageRequestHandler : public QObject
{
    Q_OBJECT
private:
    QNetworkAccessManager* manager;
    QMap<QString, QString> lastParams;
    QString UrlImage = "https://openweathermap.org/img/wn/CODE@4x.png";

private slots:
    void handleReply();

public:
    explicit ApiWeatherImageRequestHandler(QObject *parent = nullptr);

public slots:
    void makeRequest(const QString &code);

signals:
    void requestSucceeded(const QImage &response);
    void requestFailed(const QString &errorString);
};

#endif // APIWEATHERIMAGEREQUESTHANDLER_H
