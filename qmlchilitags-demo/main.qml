import QtQuick 2.2
import QtQuick.Window 2.1
import Chilitags 1.0
import QtMultimedia 5.0

Window {
    visible: true
    width: 360
    height: 360

    Camera {
        id: camera
    }

    ChilitagsDetection {
        id: detection
        source: camera

        ChilitagsObject {
            id: first
            name: "tag_84"
        }

        ChilitagsObject {
            id: second
            name: "tag_64"
        }
    }

    Image {
        id: firstimg
        source: "qrc:/qt-logo.png"
        mirror: !first.visible
        x: first.x
        y: first.y
        //transform: Translate {
        //    x:300
        //    y:300
        //}
    }

    Image {
        id: secondimg
        source: "qrc:/qt-logo.png"
        mirror: !second.visible
        x: second.x
        y: second.y
    }

    Rectangle {
        id: line
        color: "red"
        x: Math.min(first.x, second.x)
        y: Math.min(first.y, second.y)
        height: 1
        width: Math.sqrt(
                   (second.y-first.y)*(second.y-first.y) +
                   (second.x-first.x)*(second.x-first.x) )
        rotation: Math.atan2(first.y-second.y, first.x-second.x)*180.0/Math.PI;
        transformOrigin: Item.TopLeft
    }

    Text {
        text: JSON.stringify(detection.tags)
        anchors.centerIn: parent
    }

    VideoOutput {
        id: feedback
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        width: 160
        height: 120
        source: detection
    }

    Text {
        id:startButton
        text: "start"
        anchors.margins: 10
        anchors.left: parent.left
        anchors.top: parent.top

        MouseArea {
            anchors.fill: parent
            onClicked: camera.start()

        }
    }

    Text {
        id:stopButton
        text: "stop"
        anchors.margins: 10
        anchors.left: startButton.right
        anchors.top: parent.top

        MouseArea {
            anchors.fill: parent
            onClicked: camera.stop()
        }
    }


    Text {
        id:quitButton
        text: "quit"
        anchors.margins: 10
        anchors.left: stopButton.right
        anchors.top: parent.top

        MouseArea {
            anchors.fill: parent
            onClicked: Qt.quit()
        }
    }

}
