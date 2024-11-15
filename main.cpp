#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QUrlQuery>
#include <QFile>
#include <QSettings>
#include <QString>
#include <QDir>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QQmlContext>

#include "apiweatherdatarequesthandler.h"
#include "apiweatherimagerequesthandler.h"
#include "currentweatherdata.h"

#define INPUT_FILE "../../config.ini"


using namespace std;

/**
 * Creates a default configuration file at the specified file path.
 *
 * This function creates an INI format configuration file with a "General"
 * group, initializing "apiKey" and "city" values to empty strings. It logs
 * a message indicating the creation of the file.
 *
 * @param filePath The path where the configuration file should be created.
 */
void createDefaultConfigFile(const QString& filePath) {
    QSettings settings(filePath, QSettings::IniFormat);

    settings.beginGroup("General");
    settings.setValue("apiKey", QString());
    settings.setValue("city", QString());
    settings.endGroup();

    qDebug() << "Default config file created at:" << filePath;
}


/**
 * Loads the configuration from the specified file path.
 *
 * This function reads the configuration from the specified file path and
 * loads the "apiKey" and "city" values into the corresponding arguments.
 *
 * @param filePath The path where the configuration file is located.
 * @param apiKey The API key to be loaded from the configuration file.
 * @param city The city to be loaded from the configuration file.
 */
void loadConfig(const QString& filePath, QString& apiKey, QString& city) {
    QSettings settings(filePath, QSettings::IniFormat);
    
    // Api key
    apiKey = settings.value("General/apiKey").toString();
    if (apiKey.isEmpty()) { qWarning() << "The API key is empty in the config file."; }

    // City
    city = settings.value("General/city").toString();
    if (city.isEmpty()) { qWarning() << "The city is empty in the config file."; }
};

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);

    CurrentWeatherData curWeatherData;
    QString apiKey;
    QString city;
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


    // Check if the config file exists, create it if it doesn't
    if (!QFile(INPUT_FILE).exists()) {
        qDebug() << "Config file does not exist. Creating a default config file...";
        createDefaultConfigFile(INPUT_FILE);
    }

    // Load data from the config file
    loadConfig(INPUT_FILE, apiKey, city);

    weatherDataApiHandler.makeRequest(ApiWeatherDataRequestHandler::UrlWeather,{
        {"units", "metric"},
        {"lang", "fr"},
        {"q", city},
        {"appid", apiKey},
    }, 90
    );

    return app.exec();
}
