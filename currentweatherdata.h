#ifndef CURRENTWEATHERDATA_H
#define CURRENTWEATHERDATA_H

#include <QObject>
#include <QString>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDateTime>
#include <QImage>
#include <QBuffer>
#include <QByteArray>

class CurrentWeatherData : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString cityName READ cityName NOTIFY cityNameChanged)
    Q_PROPERTY(double temperature READ temperature NOTIFY temperatureChanged)
    Q_PROPERTY(double feelsLike READ feelsLike NOTIFY feelsLikeChanged)
    Q_PROPERTY(double tempMin READ tempMin NOTIFY tempMinChanged)
    Q_PROPERTY(double tempMax READ tempMax NOTIFY tempMaxChanged)
    Q_PROPERTY(double pressure READ pressure NOTIFY pressureChanged)
    Q_PROPERTY(double humidity READ humidity NOTIFY humidityChanged)
    Q_PROPERTY(QString sunrise READ sunrise NOTIFY sunriseChanged)
    Q_PROPERTY(QString sunset READ sunset NOTIFY sunsetChanged)
    Q_PROPERTY(QString description READ description NOTIFY descriptionChanged)
    Q_PROPERTY(QString replyDateTime READ replyDateTime NOTIFY replyDateTimeChanged)
    Q_PROPERTY(QString weatherImage READ weatherImage NOTIFY weatherImageChanged)


public:
    explicit CurrentWeatherData(QObject *parent = nullptr);

    QString cityName() const;
    double temperature() const;
    double feelsLike() const;
    double tempMin() const;
    double tempMax() const;
    double pressure() const;
    double humidity() const;
    QString sunrise() const;
    QString sunset() const;
    QString description() const;
    QString replyDateTime() const;
    QString imageCode() const;
    QString weatherImage() const;

    void updateCityName(const QString &cityName);
    void updateTemperature(const double &temperature);
    void updateFeelsLike(const double &feelsLike);
    void updateTempMin(const double &tempMin);
    void updateTempMax(const double &tempMax);
    void updatePressure(const double &pressure);
    void updateHumidity(const double &humidity);
    void updateSunrise(const QDateTime &sunrise);
    void updateSunset(const QDateTime &sunset);
    void updateDescription(const QString &description);
    void updateReplyDateTime(const QDateTime &replyDateTime);
    void updateImageCode(const QString &imageCode);
    void updateWeatherImage(const QImage &weatherImage);

public slots:
    void processCurrentWeatherData(const QString &response);

signals:
    void cityNameChanged();
    void temperatureChanged();
    void feelsLikeChanged();
    void tempMinChanged();
    void tempMaxChanged();
    void pressureChanged();
    void humidityChanged();
    void sunriseChanged();
    void sunsetChanged();
    void descriptionChanged();
    void replyDateTimeChanged();
    void weatherImageChanged();
    void imageCodeChanged(const QString &imageCode);

private:
    QString m_cityName = "";
    double m_temperature = 0;
    double m_feelsLike = 0;
    double m_tempMin = 0;
    double m_tempMax = 0;
    double m_pressure = 0;
    double m_humidity = 0;
    QDateTime m_sunrise;
    QDateTime m_sunset;
    QString m_description = "";
    QDateTime m_replyDateTime;
    QString m_imageCode = "";
    QImage m_weatherImage;
};

#endif // CURRENTWEATHERDATA_H
