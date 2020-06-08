import QtQuick 2.0
import QtQuick.Window 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.4

Window {
    visible: true
    width: 640
    height: 480

    property int previousFirst: 0
    property int previousLast: 0
    property int lastPivot: -1
    property int prevF: -1
    property int prevL: -1

    Timer {
        id: loop
        running: false
        repeat: true
        interval: 300

        property QtObject impl: QtObject {
            /// Changes to be applied to array
            property var changes: []
            /// Index of current change
            property int index: 0
            /// State of current change animation.
            /// Animation can have 3 states:
            ///  * 0: make elements red
            ///  * 1: swap their values
            ///  * 2: back elements to normal
            property int state: 0
        }

        function run(changes) {
            impl.changes = changes;
            loop.start();
        }

        onTriggered: {
            if (impl.changes.length == 0) {
                return stop();
            }

            var change = impl.changes[impl.index];

            if (change.type === "Swap"){
//                switch (impl.state) {
//                    case 0:
//                        array.switchColor(change.first);
//                        array.switchColor(change.second);
//                        impl.state = 1;
//                        break;

//                    case 1:
                        array.swapValues(change.first, change.second);
//                        impl.state = 2;
//                        break;

//                    case 2:
//                        array.switchColor(change.first);
//                        array.switchColor(change.second);
//                        impl.state = 0;

                        if (impl.index == impl.changes.length - 1) {
                            impl.index = 0;
                            if (prevF != -1){
                                array.switchColor(prevL);
                                array.switchColor(prevF);
                            }
                            prevL = -1;
                            prevF = -1;
                            return stop();
                        }

                        ++impl.index;
//                        break;
//                }
            }
            else if (change.type == "Compare"){
                if (prevF != -1){
                    array.switchColor(prevL);
                    array.switchColor(prevF);
                }

                var item1 = array.get(change.first);
                var item2 = array.get(change.first);

                array.switchColor(change.first);
                array.switchColor(change.second);

                prevL = change.second;
                prevF = change.first;

                impl.index++;
                if (impl.index == impl.changes.length - 1) {
                    impl.index = 0;
                    prevL = -1;
                    prevF = -1;
                    return stop();
                }
            }
            else {
                impl.index++;
            }

//            else if (change.type == "SelectSubrange"){
//                //array.showRange(change.first, change.second, 0);
//                impl.index++;
//                if (impl.index == impl.changes.length - 1) {
//                    impl.index = 0;
//                    return stop();
//                }
//            }
//            else if (change.type == "SelectPivot"){
//                //array.showPivot(change.value, 0);
//                impl.index++;
//                if (impl.index == impl.changes.length - 1) {
//                    impl.index = 0;
//                    return stop();
//                }
//            }
//            else if (change.type == "MergeSubranges"){
//                //array.showRange(change.first, change.second, 0);
//                impl.index++;
//                if (impl.index == impl.changes.length - 1) {
//                    impl.index = 0;
//                    return stop();
//                }
//            }
        }
    }

    RowLayout {
        id: rowLayout
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
                id: items
                ListElement { text: "Selection" }
                ListElement { text: "Insertion" }
                ListElement { text: "Bubble" }
                ListElement { text: "Quick" }
                ListElement { text: "Merge" }
                ListElement { text: "Heap" }
            }

            onCurrentIndexChanged: {
                sort.selectSortType(items.get(currentIndex).text);
            }
        }

        RowLayout {
            id: mainLayout

            Rectangle {
                Layout.fillWidth: true
                Layout.fillHeight: true
                color: "grey"

                TextInput {
                    id: valueInput
                    anchors.fill: parent
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    validator: RegExpValidator { regExp: /\d{1,4}(?:,\d{1,4})+$/ }
                    font.pixelSize: 20

                    Keys.onReturnPressed: {
                        mainLayout.pushValue();
                    }
                }
            }

            Button {
                text: "Add"
                Layout.fillHeight: true

                onClicked: {
                    mainLayout.pushValue();
                }
            }
            Button {
                text: "Start"
                Layout.fillHeight: true

                onClicked: {
                    loop.run(sort.execute());
                }
            }
            Button {
                text: "Clear"
                Layout.fillHeight: true

                onClicked: {
                    array.clear();
                    sort.clear();
                }
            }

            function pushValue() {
                if (valueInput.text == "") {
                    /// Ignore dummy clicking
                    return;
                }

                sort.addValue(valueInput.text);
                array.append({ value: valueInput.text , active: false });
                valueInput.text = "";
            }
        }
    }

    RowLayout {
        id: speedControls
        anchors.top: rowLayout.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: 5
        height: 60
        anchors.topMargin: rowLayout.height + 5
        spacing: 5
        z:2

        Button {
            id: fasterButton
            Layout.fillHeight: true
            text: "Faster"

            onClicked: {
                if (loop.interval > 0) {
                    loop.interval -= 50;
                } 
            }
        }
        Button {
            id: slowerButton
            anchors.left: fasterButton.right
            Layout.fillHeight: true
            text: "Slower"

            onClicked: {
                if (loop.interval < 500) {
                    loop.interval += 50;
                }
            }
        }

        ComboBox{
            id: orderType
            width:20
            Layout.fillHeight: true
            anchors.left: slowerButton.right
            anchors.margins: 5

            model: ["Asc", "Desc"]

            onCurrentTextChanged: {
                sort.selectOrderType(orderType.currentText);
            }
        }

        ComboBox{
            id: containerType
            width:50
            Layout.fillHeight: true
            anchors.left: orderType.right
            anchors.margins: 5

            model: ["Vector", "List"]

            onCurrentTextChanged: {
                sort.selectContainerType(containerType.currentText);
            }
        }
    }

    ScrollView{
        anchors.top: speedControls.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        anchors.topMargin: rowLayout.height + speedControls.height - 40

        Flickable {
            id: flickable
            clip: true

            ScrollBar.horizontal: ScrollBar {
                parent: flickable.parent
                policy: ScrollBar.AlwaysOn
                interactive: true
            }
        }

        ListView {
            spacing: 5
            orientation: ListView.Horizontal
            z: 1

            delegate: Rectangle {
                width: 120
                height: 120
                border.color: "black"
                color: active ? "red" : "lightblue"
                border.width: 2
                radius: 5

                Text {
                    anchors.centerIn: parent
                    font.bold: true
                    font.pointSize: 20
                    text: value
                }
            }

            model: ListModel {
                id: array

                function switchColor(index) {
                    var item = array.get(index);
                    array.set(index, { active: !item.active })
                }

                function swapValues(first, second) {
                    var firstValue = array.get(first).value;
                    var secondValue = array.get(second).value;
                    array.set(first, { value: secondValue });
                    array.set(second, { value: firstValue });
                }

                function changeColor(index){
                    var item = array.get(index);
                    array.set(index, { color: "green"});
                }







                function showRange(first, last, off){
                    showPivot(0, 0, 1);
                    if (!off){
                        for (let j = previousFirst; j <= previousLast; j++)
                            array.set(j, { color: "lightblue" })
                        for (let i = first; i <= last; i++)
                            array.set(i, { color: "grey" })
                        previousFirst = first;
                        previousLast = last;
                    }
                    else {
                        for (let j = previousFirst; j <= previousLast; j++)
                            array.set(j, { color: "lightblue" })
                        previousFirst = 0;
                        previousLast = 0;
                    }
                }

                function showPivot(index, off){
                    if(!off){
                        if (lastPivot != -1)
                            array.set(lastPivot, { color: "grey" })
                        array.set(index, { color: "darkgrey" });
                        lastPivot = index;
                    }
                    else {
                        array.set(lastPivot, { color: "grey" });
                        lastPivot = -1;
                    }
                }






            }
        }
    }
}
