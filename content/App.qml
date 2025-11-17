import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Window {
    width: 1024
    height: 768
    visible: true
    title: "Project Heimdall - Surveillance Grid"
    color: "#1e1e1e"

    ColumnLayout {
        anchors.fill: parent
        spacing: 10

        Text {
            Layout.alignment: Qt.AlignHCenter
            text: "Live Surveillance Feed"
            color: "#00ff00"
            font.pixelSize: 24
            font.bold: true
        }

        GridLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true
            columns: 2
            rows: 2
            columnSpacing: 5
            rowSpacing: 5

            // --- CAM 1 TILE ---
            Rectangle {
                Layout.fillWidth: true
                Layout.fillHeight: true
                color: "black"
                border.color: "#00ff00"
                border.width: 1
                clip: true  // <-- THIS IS THE FIX (was "clips")

                Image {
                    id: cam1
                    anchors.fill: parent
                    fillMode: Image.PreserveAspectFit
                    cache: false
                    source: "image://live/cam1"
                }
                
                Timer {
                    interval: 30 // ~30 FPS
                    running: true
                    repeat: true
                    onTriggered: {
                        cam1.source = "image://live/cam1?t=" + Date.now()
                    }
                }

                Text {
                    anchors.top: parent.top
                    anchors.left: parent.left
                    anchors.margins: 5
                    text: "CAM 01 [LIVE]"
                    color: "white"
                    font.bold: true
                    style: Text.Outline
                    styleColor: "black"
                }
            }

            // Placeholder for Cam 2
            Rectangle {
                Layout.fillWidth: true
                Layout.fillHeight: true
                color: "#101010"
                border.color: "#333"
                Text { anchors.centerIn: parent; text: "NO SIGNAL"; color: "#555" }
            }
        }
    }
}
