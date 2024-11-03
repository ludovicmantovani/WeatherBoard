#include "currentweatherdata.h"

CurrentWeatherData::CurrentWeatherData(QObject *parent)
    : QObject{parent}
{}

QString CurrentWeatherData::cityName() const {return m_cityName;}
void CurrentWeatherData::updateCityName(const QString &cityName) {
    if (m_cityName != cityName) {
        m_cityName = cityName;
        emit cityNameChanged();
    }
}

double CurrentWeatherData::temperature() const {return m_temperature;}
void CurrentWeatherData::updateTemperature(const double &temperature)
{
    if (m_temperature != temperature){
        m_temperature = temperature;
        emit temperatureChanged();
    }
}


double CurrentWeatherData::feelsLike() const {return m_feelsLike;}
void CurrentWeatherData::updateFeelsLike(const double &feelsLike)
{
    if (m_feelsLike != feelsLike){
        m_feelsLike = feelsLike;
        emit feelsLikeChanged();
    }
}

double CurrentWeatherData::tempMin() const {return m_tempMin;}
void CurrentWeatherData::updateTempMin(const double &tempMin)
{
    if (m_tempMin != tempMin){
        m_tempMin = tempMin;
        emit tempMinChanged();
    }
}

double CurrentWeatherData::tempMax() const {return m_tempMax;}
void CurrentWeatherData::updateTempMax(const double &tempMax)
{
    if (m_tempMax != tempMax){
        m_tempMax = tempMax;
        emit tempMaxChanged();
    }
}

double CurrentWeatherData::pressure() const {return m_pressure;}
void CurrentWeatherData::updatePressure(const double &pressure)
{
    if (m_pressure != pressure){
        m_pressure = pressure;
        emit pressureChanged();
    }
}

double CurrentWeatherData::humidity() const {return m_humidity;}
void CurrentWeatherData::updateHumidity(const double &humidity)
{
    if (m_humidity != humidity){
        m_humidity = humidity;
        emit humidityChanged();
    }
}

QString CurrentWeatherData::sunrise() const {return m_sunrise.toString("hh:mm");}
void CurrentWeatherData::updateSunrise(const QDateTime &sunrise)
{
    if (m_sunrise != sunrise){
        m_sunrise = sunrise;
        emit sunriseChanged();
    }
}

QString CurrentWeatherData::sunset() const {return m_sunset.toString("hh:mm");}
void CurrentWeatherData::updateSunset(const QDateTime &sunset)
{
    if (m_sunset != sunset){
        m_sunset = sunset;
        emit sunsetChanged();
    }
}

QString CurrentWeatherData::description() const {return m_description;}
void CurrentWeatherData::updateDescription(const QString &description)
{
    if (m_description != description){
        m_description = description;
        emit descriptionChanged();
    }
}

QString CurrentWeatherData::replyDateTime() const {return m_replyDateTime.toString("hh:mm");}
void CurrentWeatherData::updateReplyDateTime(const QDateTime &replyDateTime)
{
    if (m_replyDateTime != replyDateTime){
        m_replyDateTime = replyDateTime;
        emit replyDateTimeChanged();
    }
}

QString CurrentWeatherData::weatherImage() const {
    QByteArray byteArray;
    QBuffer buffer(&byteArray);
    buffer.open(QIODevice::WriteOnly);
    m_weatherImage.save(&buffer, "PNG");
    return QString::fromLatin1(byteArray.toBase64().data());
}
void CurrentWeatherData::updateWeatherImage(const QImage &weatherImage)
{
    if (m_weatherImage != weatherImage){
        m_weatherImage = weatherImage;
        emit weatherImageChanged();
    }
}

QString CurrentWeatherData::imageCode() const {return m_imageCode;}
void CurrentWeatherData::updateImageCode(const QString &imageCode){
    if (m_imageCode != imageCode){
        m_imageCode = imageCode;
        emit imageCodeChanged(imageCode);
    }
}

void CurrentWeatherData::processCurrentWeatherData(const QString &response) {
    QJsonDocument document = QJsonDocument::fromJson(response.toUtf8());
    QJsonObject rootObj = document.object();

    updateCityName(rootObj["name"].toString());
    updateReplyDateTime(QDateTime::fromSecsSinceEpoch(rootObj["dt"].toVariant().toLongLong()));

    QJsonObject mainObj = rootObj["main"].toObject();
    updateTemperature(mainObj["temp"].toDouble());
    updateFeelsLike(mainObj["feels_like"].toDouble());
    updateTempMin(mainObj["temp_min"].toDouble());
    updateTempMax(mainObj["temp_max"].toDouble());
    updatePressure(mainObj["pressure"].toDouble());
    updateHumidity(mainObj["humidity"].toDouble());

    QJsonObject sysObj = rootObj["sys"].toObject();
    updateSunrise(QDateTime::fromSecsSinceEpoch(sysObj["sunrise"].toVariant().toLongLong()));
    updateSunset(QDateTime::fromSecsSinceEpoch(sysObj["sunset"].toVariant().toLongLong()));

    QJsonArray weatherArray = rootObj["weather"].toArray();
    QJsonObject weather = weatherArray[0].toObject();
    updateDescription(weather["description"].toString());
    updateImageCode(weather["icon"].toString());

}
