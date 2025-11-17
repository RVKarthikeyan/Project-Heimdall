import QtQuick
import QtQuick.Controls

Window {
    width: 1024
    height: 768
    visible: true
    title: "Project Heimdall - Surveillance Grid"
    color: "#1e1e1e"

    Text {
        anchors.centerIn: parent
        text: "Heimdall Online\nAwaiting Camera Feeds..."
        color: "#00ff00" // Hacker green
        font.pixelSize: 24
        horizontalAlignment: Text.AlignHCenter
    }
}
