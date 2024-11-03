#ifndef APIWEATHERDATAREQUESTHANDLER_H
#define APIWEATHERDATAREQUESTHANDLER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QUrlQuery>
#include <QDateTime>
#include <QTimer>

class ApiWeatherDataRequestHandler : public QObject
{
    Q_OBJECT
private:
    QNetworkAccessManager* manager;
    QTimer* updateTimer;
    QDateTime lastRequestTime;
    int updateIntervalSeconds;

    QString lastUrl;
    QMap<QString, QString> lastParams;

private slots:
    void handleReply();

public:
    explicit ApiWeatherDataRequestHandler(QObject *parent = nullptr);
    void makeRequest(const QString &url, const QMap<QString, QString> &params, int updateInterval = 0);
    inline static const QString UrlWeather = "https://api.openweathermap.org/data/2.5/weather";

signals:
    void requestSucceeded(const QString &response);
    void requestFailed(const QString &errorString);
};

#endif // APIWEATHERDATAREQUESTHANDLER_H
