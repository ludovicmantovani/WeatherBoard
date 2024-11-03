#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QUrlQuery>
#include <QFile>
#include <QDir>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QQmlContext>

#include "apiweatherdatarequesthandler.h"
#include "apiweatherimagerequesthandler.h"
#include "currentweatherdata.h"

#define INPUT_FILE "../../data.txt"


using namespace std;

qsizetype getApiKey(const QString& filePath, QString& apiKey) {
    QFile dataFile(filePath);

    // Check if the file exists
    if (!dataFile.exists()) {
        qWarning() << dataFile.fileName() << "does not exist.";
        return -1;
    }

    // Get the file permissions
    QFileDevice::Permissions filePermissions = dataFile.permissions();
    bool fileReadOk = filePermissions & QFileDevice::ReadUser;
    bool fileWriteOk = filePermissions & QFileDevice::WriteUser;

    qDebug() << QString("%1 is %2 for reading and %3 for writing.").arg(
        dataFile.fileName(), fileReadOk ? "OK" : "KO", fileWriteOk ? "OK" : "KO");

    // Check if the file is readable
    if (!fileReadOk) return -1;

    // Open the file in read-only mode
    if (dataFile.open(QIODevice::ReadOnly)) {
        QTextStream in(&dataFile);
        apiKey = in.readLine().simplified();  // Read and clean up the first line
        dataFile.close();
    }

    // Check if the API key is empty or too short
    if (apiKey.isEmpty() || apiKey.length() < 3) {
        qWarning() << "The API key is either empty or too short.";
        return -1;
    }

    // Display the masked API key for debugging
    qDebug() << "Masked API key:" <<
        apiKey.front() + QString(apiKey.length() - 2, '*') + apiKey.back();

    return apiKey.length();
}


int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);

    CurrentWeatherData curWeatherData;
    QString apiKey;
    ApiWeatherDataRequestHandler weatherDataApiHandler;
    ApiWeatherImageRequestHandler weatherImageApiHandler;


    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("currentWeatherData", &curWeatherData);
    engine.loadFromModule("WeatherBoard", "Main");


    QObject::connect(&weatherDataApiHandler, &ApiWeatherDataRequestHandler::requestSucceeded, &curWeatherData, &CurrentWeatherData::processCurrentWeatherData);
    QObject::connect(&weatherDataApiHandler, &ApiWeatherDataRequestHandler::requestFailed, [](const QString &error) {
        qDebug() << "Weather data request failed with error:" << error;
    });

    QObject::connect(&weatherImageApiHandler, &ApiWeatherImageRequestHandler::requestSucceeded, &curWeatherData, &CurrentWeatherData::updateWeatherImage);
    QObject::connect(&weatherImageApiHandler, &ApiWeatherImageRequestHandler::requestFailed, [](const QString &error) {
        qDebug() << "Weather image request failed with error:" << error;
    });

    QObject::connect(&curWeatherData, &CurrentWeatherData::imageCodeChanged, &weatherImageApiHandler, &ApiWeatherImageRequestHandler::makeRequest);


    getApiKey(INPUT_FILE, apiKey);

    weatherDataApiHandler.makeRequest(ApiWeatherDataRequestHandler::UrlWeather,{
        {"units", "metric"},
        {"lang", "fr"},
        {"q", "Guyancourt"},
        {"appid", apiKey},
    }, 90
    );


    //sendWeatherRequest(apiKey, manager);


    return app.exec();
}
