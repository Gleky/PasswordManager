import QtQuick 2.0
import QtQuick.Controls 2.5


Button {
    property int rectHeight: 25
    property int rectWidth: 30
    property color color: "#606060"

    font.capitalization: Font.MixedCase

    background: Rectangle {
        implicitHeight:  rectHeight
        implicitWidth: rectWidth
        color: parent.color
        radius: 5
        opacity: 0.6
    }
}
