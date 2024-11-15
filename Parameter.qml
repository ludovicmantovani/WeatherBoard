import QtQuick
import QtQuick.Controls

Item {
    Rectangle {
      anchors.fill: parent
      color: backgroundColor ? backgroundColor : "red"

      Button {
          anchors.top: parent.top
          anchors.left: parent.left
          anchors.margins: 5
          text: "City"
          height: parent.height / 10
          width: parent.width / 5
          onClicked: {
              myStackView.push("CityInfo.qml");
          }
      }

      Switch {
          id: temp_format_switch
          anchors.centerIn: parent
          checked: celsius
          onCheckedChanged:
          {
              if (celsius != checked) celsius = checked;
          }
      }

      Text {
          text: "Fahrenheit"
          color: "white"
          font.pixelSize: pSize
          anchors.verticalCenter: temp_format_switch.verticalCenter
          anchors.right: temp_format_switch.left
          anchors.margins: 5
      }

      Text {
          text: "Celsius"
          color: "white"
          font.pixelSize: pSize
          anchors.verticalCenter: temp_format_switch.verticalCenter
          anchors.left: temp_format_switch.right
          anchors.margins: 5
      }
    }
}
