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

        // The Surveillance Grid
        GridLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true
            columns: 2
            rows: 2
            columnSpacing: 5
            rowSpacing: 5

            // Camera 1 Tile
            Rectangle {
                Layout.fillWidth: true
                Layout.fillHeight: true
                color: "black"
                border.color: "#00ff00"
                border.width: 1

                Image {
                    id: cam1
                    anchors.fill: parent
                    fillMode: Image.PreserveAspectFit
                    // This URL triggers our C++ LiveImageProvider
                    // "image://" = protocol
                    // "live" = the name we registered in main.cpp
                    // "cam1" = the ID passed to requestImage()
                    source: "image://live/cam1"
                    
                    // Disable caching so we get new frames (crucial for video!)
                    cache: false 
                }

                Text {
                    anchors.top: parent.top
                    anchors.left: parent.left
                    anchors.margins: 5
                    text: "CAM 01 [ONLINE]"
                    color: "white"
                    font.bold: true
                    style: Text.Outline
                    styleColor: "black"
                }
            }

            // Placeholder for Cam 2 (Empty for now)
            Rectangle {
                Layout.fillWidth: true
                Layout.fillHeight: true
                color: "#101010"
                border.color: "#333"
                
                Text {
                    anchors.centerIn: parent
                    text: "NO SIGNAL"
                    color: "#555"
                }
            }
        }
    }
}
