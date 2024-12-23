import QtQuick

Item {

    function convertTemperature(temp) {
        if (celsius) {
            return temp + "°C";
        } else {
            var fahrenheitTemp = (temp * 9 / 5) + 32;
            return fahrenheitTemp.toFixed(1) + "°F";
        }
    }

    Rectangle {
        anchors.fill: parent
        color: "steelblue"
        id: root
        opacity: 1

        Text {
            id: name
            text: currentWeatherData.cityName;
            color: "white"
            font.pointSize: h1Size
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
        }

        Timer {
                id: updateTimer
                interval: 1000
                repeat: true
                running: true
                onTriggered: {
                    currentTime = new Date()
                }
            }

        Text {
            id: curr_date
            text: currentTime.toLocaleString(Qt.locale("fr_FR"), "dddd d MMMM yyyy HH'h'mm")
            color: "white"
            font.pointSize: h2Size
            anchors.horizontalCenter: name.horizontalCenter
            anchors.top: name.bottom
        }

        Rectangle {
            id: name_sep
            width: parent.width * 3/4
            radius: width
            height: 2
            color: "white"
            anchors.horizontalCenter: name.horizontalCenter
            anchors.top: curr_date.bottom
            anchors.topMargin: 20
        }

        Image {
            id: desc_img
            height: imgSize
            width: height
            anchors.top: name_sep.bottom
            anchors.topMargin: -30
            anchors.horizontalCenter: name.horizontalCenter
            fillMode: Image.PreserveAspectFit
            source: "data:image/png;base64," + currentWeatherData.weatherImage
        }

        Text {
            id: desc_text
            text: currentWeatherData.description
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: desc_img.bottom
            anchors.topMargin: -55
            font.pointSize: pSize
            color: "white"
        }

        Text {
            id: temp_feels
            text: convertTemperature(currentWeatherData.feelsLike)
            anchors.horizontalCenter: parent.horizontalCenter
            font.pointSize: pSize
            color: "white"
            anchors.top: desc_text.bottom
            anchors.topMargin: 10
        }

        Text {
            id: temp_min
            text: convertTemperature(currentWeatherData.tempMin)
            anchors.top: temp_feels.bottom
            anchors.right: temp_feels.left
            font.pointSize: sSize
            color: "white"
            anchors.topMargin: 5
            anchors.rightMargin: 20
        }

        Text {
            id: temp_max
            text: convertTemperature(currentWeatherData.tempMax)
            anchors.left: temp_feels.right
            anchors.top: temp_feels.bottom
            font.pointSize: sSize
            color: "white"
            anchors.topMargin: 5
            anchors.leftMargin: 20
        }

        Text {
            id: temp_curr
            text: convertTemperature(currentWeatherData.temperature)
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.baseline: temp_min.baseline
            font.pointSize: sSize
            color: "white"
            anchors.topMargin: 5
        }

        Text {
            id: sun
            text: "soleil"
            anchors.top: temp_curr.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            font.pointSize: sSize
            color: "white"
            anchors.topMargin: 20
        }

        Text {
            id: sunrise_time
            text: currentWeatherData.sunrise
            anchors.right: sun.left
            anchors.baseline: sun.baseline
            font.pointSize: sSize
            color: "white"
            anchors.rightMargin: 20
        }

        Text {
            id: sunset_time
            text: currentWeatherData.sunset
            anchors.left: sun.right
            anchors.baseline: sun.baseline
            font.pointSize: sSize
            color: "white"
            anchors.leftMargin: 20
        }

        Text {
            id: source
            text: "Source : OpenWeather à " + currentWeatherData.replyDateTime
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.margins: 5
            font.pointSize: ssSize
            color: "white"
        }

        Text {
            id: param
            text: "Paramètres"
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            anchors.margins: 5
            font.pointSize: sSize
            color: "white"

            MouseArea {
                anchors.fill: parent
                onClicked: myStackView.push("Parameter.qml");
            }
        }
    }
}
