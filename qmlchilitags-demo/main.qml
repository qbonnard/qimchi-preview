import QtQuick 2.2
import QtQuick.Window 2.1
import Chilitags 1.0
import QtMultimedia 5.0

Window {
    visible: true
    width: 360
    height: 360

    Camera { id: camera }

    ChilitagsDetection {
        id: detection
        source: camera

        property vector3d tagCenter : Qt.vector3d(10,10,0)

        ChilitagsObject {
            id: redTag
            name: "tag_4"
            property vector3d center : transform.times(parent.tagCenter)
        }
        ChilitagsObject {
            id: blueTag
            name: "tag_5"
            property vector3d center : transform.times(parent.tagCenter)
        }
    }

    Item {
        y:20
        transform: Scale {xScale: .5; yScale:.5}

        VideoOutput {
            anchors.top: parent.top
            anchors.left: parent.left
            source: detection
        }

        Item {
            transform: Transform { matrix: detection.projectionMatrix }
            Item {
                transform: Transform { matrix: redTag.transform }
                Rectangle {
                    color: "blue"
                    width: 20; height: 20
                    visible: redTag.visible
                }
                Image {
                    source: "qrc:/qt-logo.png";
                    width: 20; height: 20
                    visible: redTag.visible
                }
            }

            Item {
                transform: Transform { matrix: blueTag.transform }
                Rectangle {
                    color: "red"
                    width: 20; height: 20
                    visible: blueTag.visible
                }
                Image {
                    source: "qrc:/qt-logo.png";
                    width: 20; height: 20
                    visible: blueTag.visible
                }
            }


        }

        Rectangle {
            property vector3d start :  detection.projectionMatrix.times(redTag.center)
            property vector3d end :  detection.projectionMatrix.times(blueTag.center)
            id: line
            color: "magenta"
            x: start.x
            y: start.y
            height: 1
            width: Math.sqrt(
                       (end.y-start.y)*(end.y-start.y) +
                       (end.x-start.x)*(end.x-start.x) )
            rotation: Math.atan2(end.y-start.y, end.x-start.x)*180.0/Math.PI;
            transformOrigin: Item.TopLeft
        }
    }

    Rectangle {
        color: "#ffffff"
        id:startButton
        width: 50
        height: 20
        anchors.left: parent.left
        anchors.top: parent.top
        Text {
            text: "start"
            anchors.centerIn: parent
        }
        MouseArea {
            anchors.fill: parent
            onClicked: camera.start()
        }
    }

    Rectangle {
        color: "#ffffff"
        id:stopButton
        width: 50
        height: 20
        anchors.left: startButton.right
        anchors.top: startButton.top
        Text {
            text: "stop"
            anchors.centerIn: parent
        }
        MouseArea {
            anchors.fill: parent
            onClicked: camera.stop()
        }
    }

    Rectangle {
        color: "#ffffff"
        id:quitButton
        width: 50
        height: 20
        anchors.left: stopButton.right
        anchors.top: stopButton.top
        Text {
            text: "quit"
            anchors.centerIn: parent
        }
        MouseArea {
            anchors.fill: parent
            onClicked: Qt.quit()
        }
    }

}
