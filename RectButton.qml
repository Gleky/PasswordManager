import QtQuick 2.0
import QtQuick.Controls 2.5


Button {
    property int rectHeight: 25
    property int rectWidth: 30

    background: Rectangle {
        implicitHeight:  rectHeight
        implicitWidth: rectWidth
        color: "#606060"
        radius: 5
        opacity: 0.6
    }
}
