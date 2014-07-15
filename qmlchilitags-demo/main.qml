import QtQuick 2.2
import QtQuick.Window 2.1
import Chilitags 1.0

Window {
    visible: true
    width: 360
    height: 360

    ChilitagsCamera {
        id: chilitagsCamera
        anchors.fill: parent
        visible: false
        Component.onCompleted: {
            chilitagsCamera.start();
        }
    }

    ChilitagsObject {
        id: first
        tags: chilitagsCamera.tags
        name: "tag_84"
    }

    ChilitagsObject {
        id: second
        tags: chilitagsCamera.tags
        name: "tag_64"
    }

    Image {
        id: firstimg
        source: "qrc:/qt-logo.png"
        mirror: !second.visible
        x: second.x
        y: second.y
    }

    Image {
        id: secondimg
        source: "qrc:/qt-logo.png"
        mirror: !first.visible
        x: first.x
        y: first.y
        //transform: Translate {
        //    x:300
        //    y:300
        //}
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
        text: line.rotation.toString()
        anchors.centerIn: parent
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            Qt.quit();
        }
    }
}
