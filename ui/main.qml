import QtQuick 2.0
import QtQuick.Window 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1

Window {
    id: all

    visible: true
    width: 640
    height: 480

    property int first: 0;
    property int second: 0;
    property int speed: 3;


    Timer {
        id: _actionTimerColor1
        interval: speed * 335
        running: false
        repeat: false
        onTriggered: {
            array.set(first, {col: "red"});
            array.set(second, {col: "red"});
        }
    }

    Timer {
        id: _actionTimerName1
        interval: speed * 670
        running: false
        repeat: false
        onTriggered: {
            var firstName = array.get(first).textList;
            var secondName = array.get(second).textList;
            array.set(first, { textList: secondName });
            array.set(second, { textList: firstName });
        }
    }

    Timer {
        id: _actionTimerColor3
        interval: speed * 1000
        running: false
        repeat: false
        onTriggered: {
            array.set(first, {col: "lightblue"});
            array.set(second, {col: "lightblue"})
        }
    }

    Connections {
        target: sorting

        onSendChange: {
            all.first = first;
            all.second = second;
            _actionTimerColor1.start();
            _actionTimerName1.start();
            _actionTimerColor3.start();
        }
    }

    RowLayout {
        id: _rowLayout
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: 5
        height: 60

        spacing: 5
        z:2

        ComboBox {
            width:100
            Layout.fillHeight: true

            model: ListModel {
                id: cdItems
                ListElement { text: "SelectionSort" }
                ListElement { text: "BubbleSort" }
                ListElement { text: "QuickSort" }
                ListElement { text: "InsertionSort" }
                ListElement { text: "MergeSort" }
                ListElement { text: "HeapSort" }
            }

            onCurrentIndexChanged: {
                sorting.selectType(cdItems.get(currentIndex).text);
            }
        }

        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: "grey"

            TextInput {
                id: _textInput
                anchors.fill: parent
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter

                validator: RegExpValidator { regExp: /\d{1,4}(?:,\d{1,4})+$/ }

                font.pixelSize: 20

                Keys.onReturnPressed: {
                    array.update();
                }
            }
        }

        Button {
            id: _button
            text: qsTr("Add")
            Layout.fillHeight: true

            onClicked: {
                array.update();
            }
        }

        Button {
            id: _buttonStart
            text: qsTr("Start")
            Layout.fillHeight: true

            onClicked: {
                sorting.start();
            }
        }
    }

    RowLayout {
        id: _rowLayoutSpeed
        anchors.top: _rowLayout.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: 5
        height: 60

        anchors.topMargin: _rowLayout.height + 5

        spacing: 5
        z:2

        Button {
            id: _faster
            Layout.fillHeight: true
            text: "Faster"
            onClicked: {
                speed = speed + 1;
                sorting.speedUp();
            }
        }
        Button {
            id: _slower
            anchors.left: _faster.right
            Layout.fillHeight: true
            text: "Slower"
            onClicked: {
                sorting.speedDown();
            }
        }
    }

    ListView {
        id: _listView

        anchors.top: _rowLayoutSpeed.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        anchors.topMargin: _rowLayout.height + _rowLayoutSpeed.height - 40

        spacing: 5
        orientation: ListView.Horizontal
        z: 1

        delegate: Rectangle {
            id: _elem

            width: 120
            height: 120
            color: col
            border.color: "black"
            border.width: 2
            radius: 5

            Text {
                anchors.centerIn: _elem
                font.bold: true
                font.pointSize: 20

                text: textList
            }
        }

        model: ListModel{
            id: array

            function update() {
                sorting.addValue(_textInput.text);
                append({ textList: _textInput.text, col: "lightblue" });
                _textInput.text = "";
            }
        }
    }
}
