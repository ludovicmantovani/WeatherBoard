import QtQuick
import QtQuick.Controls

Window {
    property int h1Size: height / 12
    property int h2Size: h1Size / 2
    property int pSize: h1Size * 2/3
    property int sSize: pSize / 2
    property int ssSize: pSize / 3
    property int imgSize: height / 2.4
    property color backgroundColor: "steelblue"
    property date currentTime: new Date()

    property bool celsius: true

    width: 640
    height: 480
    visible: true
    title: "Météo"
    color: backgroundColor
    // visibility: Window.FullScreen
    // visibility: Window.Maximized


    StackView{
        id: myStackView
        anchors.fill: parent
        initialItem: "CityInfo.qml"
    }
}
