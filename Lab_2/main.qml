import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.14
import QtQuick.Controls 2.5




ApplicationWindow {
    Popup {
        id: incorrectpassword
        parent: Overlay.overlay
        x: Math.round((parent.width - width) / 2)
        y: Math.round((parent.height - height) / 2)
        width: 400
        height: 350
        modal: true
        background: Rectangle {
            color: "white"
            border.color: "red"
            radius: 100

        }

        ColumnLayout{
            Layout.fillWidth: true
            anchors.fill: parent

            Label {
                id: incorrectpasswordlabel
                Layout.alignment: Qt.AlignCenter
                font.pixelSize: 20
                text: "Вы ввели не правильный пароль!!!"
                color: "black"
            }


            Button {
                id: warningclose
                Layout.alignment: Qt.AlignCenter
                background: Rectangle {
                    radius: 20
                    border.color: "black"
                }
                contentItem: Text {
                    horizontalAlignment: Text.AlignHCenter

                    text: qsTr("  Закрыть  ")
                    font.pixelSize: 20
                }
                onClicked: {
                    incorrectpassword.visible = false

                }
            }
        }

     }
    Popup {
        id: confirmpincode
        parent: Overlay.overlay
        x: Math.round((parent.width - width) / 2)
        y: Math.round((parent.height - height) / 2)
        width: 400
        height: 350
        modal: true
        background: Rectangle {
            color: "#F0FFFF"
        }

        ColumnLayout{
            Layout.fillWidth: true
            anchors.fill: parent

            Label {
                id: confirmpin
                Layout.alignment: Qt.AlignCenter
                font.pixelSize: 20
                text: "Подтвердите pin-code!!!"
            }
            TextField{
                id: inputconfirmpin
                placeholderText: "Pin-code"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                Layout.alignment: Qt.AlignCenter
                Layout.fillWidth: true
                Layout.margins: 20
                color: "black"
                font.pixelSize: 20
                echoMode: "Password"
                background: Rectangle {
                    radius: 10
                    border.color: "black"
                }
            }

            Label {
                id: typeField
                text: ""
                visible: false
            }
            Label {
                id: indexField
                text: ""
                visible: false
            }
            Button {
                id: confirmpinclose
                Layout.alignment: Qt.AlignCenter
                background: Rectangle {
                    radius: 20
                    border.color: "black"
                }
                contentItem: Text {
                    horizontalAlignment: Text.AlignHCenter

                    text: qsTr("  Ок  ")
                    font.pixelSize: 20
                }
                onClicked: {
                    if(base.parsing(inputconfirmpin.text, "") === false){
                        incorrectpassword.visible = true
                    }
                    else {
                        base.cryptCopy(indexField.text, typeField.text, inputconfirmpin.text)
                        confirmpincode.close()
                        inputconfirmpin.clear()
                        indexField.text = ""
                        typeField.text = ""
                    }
                }
            }
        }
    }

    signal parseJson(string pin)

    visible: true
    width: 800
    height: 700
    title: qsTr("Test")

    background: Rectangle {
        color: "#F0FFFF"
    }

    ColumnLayout{
        Layout.fillWidth: true
        anchors.fill: parent

        Item {
            id: name1
            Layout.fillHeight: true
        }
        Item {
            id: name3
            Layout.fillHeight: true
        }
        TextField{
            id: pincode
            visible: true
            cursorVisible: false
            placeholderText: "Pin-code"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            Layout.alignment: Qt.AlignCenter
            Layout.fillWidth: true
            Layout.margins: 220
            color: "black"
            font.pixelSize: 20
            passwordCharacter : string
            echoMode: "Password"
            background: Rectangle {
                radius: 10
                border.color: "black"
            }
        }

        Button {
            id: authorization
            Layout.alignment: Qt.AlignCenter
            background: Rectangle {
                radius: 20
                border.color: "black"
            }
            contentItem: Text {
                horizontalAlignment: Text.AlignHCenter

                text: qsTr("  Войти  ")
                font.pixelSize: 20
            }
            onClicked: {
                if(base.parsing(pincode.text, "") === false){
                    incorrectpassword.visible = true
                }
                else {
                   pincode.visible = false
                   list.visible = true
                   authorization.visible = false
                   listView.visible = true
                }
            }
        }
        Item {
            id: name
            Layout.fillHeight: true
        }
        Item {
            id: name2
            Layout.fillHeight: true
        }
    }


    ScrollView{
        id: list
        anchors.fill: parent
        visible: false

        Layout.fillWidth: true
        Item {}

        ColumnLayout{
            anchors.fill: parent
            TextField{
                id: search
                Layout.fillWidth: true
                visible: true
                cursorVisible: false
                placeholderText: "Поиск"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                Layout.margins: 20
                color: "black"
                font.pixelSize: 20
                onEditingFinished: {
                    base.parsing(pincode.text, search.text)
                }
            }

            ListView{
                id: listView
                Layout.margins: 20
                visible: false
                Layout.fillHeight: true
                Layout.fillWidth: true
                enabled: true
                model: modal
                spacing: 10
                anchors.margins: 5
                delegate: Rectangle{
                    anchors.margins: 5
                    width: listView.width
                    height: 120
                    border.color: "grey"
                    radius: 10

                    GridLayout{
                        anchors.fill: parent
                        columns: 3

                        Image{

                            Layout.rowSpan: 3
                            Layout.fillHeight: true
                            Layout.preferredWidth: 100
                            Layout.margins: 5
                            fillMode: Image.PreserveAspectFit
                            Layout.alignment: Qt.AlignCenter
                        }
                        Label{
                            color: "black"
                            text: url
                            Layout.alignment: Qt.AlignVCenter
                            Layout.rowSpan: 3
                            Layout.preferredWidth: 120
                            font.pixelSize: 15
                        }
                        GridLayout{
                            Layout.rowSpan: 3
                            Layout.fillHeight: true
                            Layout.alignment: Qt.AlignCenter
                            columns: 1
                            rows: 1
                            Button {
                                id: copy_login
                                Layout.alignment: Qt.AlignVCenter
                                Layout.rowSpan: 1
                                Layout.preferredWidth: 170
                                background: Rectangle {
                                    radius: 20
                                    border.color: "black"
                                    color: "#aee8c5"
                                }
                                contentItem: Text {
                                    horizontalAlignment: Text.AlignHCenter
                                    verticalAlignment: Text.AlignVCenter
                                    text: "Скопировать логин"
                                    font.pixelSize: 15
                                }
                                onClicked: {
                                    confirmpincode.open()
                                    indexField.text = index
                                    typeField.text = "login"
                                }
                            }

                            Button {
                                id: copy_password
                                Layout.alignment: Qt.AlignVCenter
                                Layout.rowSpan: 1
                                Layout.preferredWidth: 170
                                background: Rectangle {
                                    radius: 20
                                    border.color: "black"
                                    color: "#e8ad8b"
                                }
                                contentItem: Text {
                                    horizontalAlignment: Text.AlignHCenter
                                    verticalAlignment: Text.AlignVCenter
                                    text: "Скопировать пароль"
                                    font.pixelSize: 15
                                }
                                onClicked: {
                                    confirmpincode.open()
                                    indexField.text = index
                                    typeField.text = "password"
                                }
                            }
                       }
                    }
                }


            }

      Button{
        id:out
        Layout.alignment: Qt.AlignCenter
        Layout.bottomMargin: 50
        background: Rectangle {
            radius: 20
            border.color: "black"
        }
        contentItem: Text {
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            text: "Выйти"
            font.pixelSize: 20
            }
        onClicked: {
            list.visible = false
            authorization.visible = true
            pincode.visible = true
            confirmpincode.visible = false

            }
        }
      }
    }
}
