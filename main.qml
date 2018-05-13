import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3
import Emoji 1.0

Window {
    visible: true
    width: 480
    height: 480
    title: qsTr("Hello Emoji")
    color: defaultColor1

    readonly property string defaultColor0: "#FFFFFF"
    readonly property string defaultColor1: "#DEDEDE"
    readonly property int defaultSpacing: 16
    readonly property int defaultRadius: defaultSpacing / 2
    readonly property int defaultEmojiSize: 48

    function composeEmojiUrl(code) {
        return "https://raw.githubusercontent.com/googlei18n/noto-emoji/master/svg/emoji_u" + code + ".svg"
    }

    EmojiLoader {
        id: emojiLoader
        source: "http://unicode.org/Public/emoji/1.0/emoji-data.txt"
    }

    EmojiModel {
        id: emojiModel
        emojiData: emojiLoader.emojiData
    }

    MessagesModel {
        id: messagesModel
        messagesData: chat.messagesData
    }

    Chat {
        id: chat
    }

    GridLayout {
        anchors.fill: parent
        anchors.margins: defaultSpacing
        columnSpacing: defaultSpacing
        columns: 1
        rowSpacing: defaultSpacing

        Rectangle {
            Layout.fillHeight: true
            Layout.fillWidth: true
            color: defaultColor0
            radius: defaultRadius

            Item {
                anchors.fill: parent
                anchors.margins: defaultSpacing
                clip: true

                ListView {
                    id: messagesView

                    anchors.fill: parent
                    delegate: messageComponent
                    model: messagesModel
                    spacing: defaultSpacing

                    onCountChanged: positionViewAtEnd()
                }
            }
        }

        RowLayout {
            Layout.fillHeight: false
            Layout.fillWidth: true
            spacing: defaultSpacing

            TextArea {
                id: input

                Layout.fillHeight: true
                Layout.fillWidth: true
                placeholderText: qsTr("Write a message...")
                textFormat: TextEdit.RichText
                verticalAlignment: TextEdit.AlignVCenter
                selectByMouse: true

                Rectangle {
                    anchors.fill: parent
                    color: defaultColor0
                    radius: defaultRadius
                    z: -1
                }

                Keys.onPressed: {
                    if (event.key === Qt.Key_Return) {
                        event.accepted = true
                        if (event.modifiers === 0) {
                            send()
                        } else if (event.modifiers | Qt.Key_Control) {
                            insertNewLine()
                        }
                    } else {
                        event.accepted = false
                    }
                }

                function insertNewLine() {
                    insertText("<br>")
                }

                function insertImage(url) {
                    if (url !== "") {
                        insertText("<img width=" + font.pixelSize + " height=" + font.pixelSize + " src=\"" + url + "\">")
                    }
                }

                function insertText(text) {
                    if (text !== "") {
                        insert(cursorPosition, text)
                    }
                }

                function send() {
                    if (length > 0) {
                        if (chat.sendMessage(text)) {
                            clear()
                        }
                    }
                }
            }

            ToolButton {
                id: toolButtonEmoji

                Layout.alignment: Qt.AlignBottom
                checked: hovered
                hoverEnabled: true

                Image {
                    anchors.fill: parent
                    source: composeEmojiUrl("1f914")
                }

                Rectangle {
                    anchors.bottom: parent.top
                    anchors.right: parent.right
                    border.color: defaultColor1
                    border.width: 1
                    clip: true
                    height: defaultEmojiSize * 5 + defaultSpacing * 2;
                    width: height
                    radius: defaultRadius
                    visible: parent.checked

                    ScrollView {
                        anchors.fill: parent
                        anchors.margins: defaultRadius

                        GridView {
                            anchors.fill: parent
                            anchors.margins: defaultRadius
                            cellHeight: defaultEmojiSize
                            cellWidth: defaultEmojiSize
                            delegate: emojiComponent
                            model: emojiModel
                        }
                    }
                }
            }

            ToolButton {
                Layout.alignment: Qt.AlignBottom

                Image {
                    anchors.fill: parent
                    source: composeEmojiUrl("1f4e8")
                }

                onClicked: input.send()
            }
        }
    }

    Component.onCompleted: input.forceActiveFocus()

    Component {
        id: messageComponent

        Rectangle {
            antialiasing: true
            border.color: defaultColor1
            border.width: 1
            color: defaultColor0
            implicitHeight: messageText.height + defaultSpacing
            implicitWidth: messageText.width + defaultSpacing
            radius: defaultRadius
            smooth: true

            Text {
                id: messageText

                anchors.centerIn: parent
                text: display
                textFormat: Text.RichText
            }
        }
    }

    Component {
        id: emojiComponent

        Item {
            height: defaultEmojiSize
            width: defaultEmojiSize

            Image {
                id: emojiImage

                anchors.centerIn: parent
                height: emojiMouseArea.containsMouse ? defaultEmojiSize : defaultEmojiSize - 8
                width: height
                source: composeEmojiUrl(code_role)
            }

            BusyIndicator {
                anchors.fill: parent
                running: emojiImage.status === Image.Loading
            }

            MouseArea {
                id: emojiMouseArea

                anchors.fill: parent
                hoverEnabled: true

                onClicked: {
                    console.log(name_role + " " + character_role + " " + composeEmojiUrl(code_role))
                    input.insertImage(composeEmojiUrl(code_role))
                    //input.insertText(character_role)
                    toolButtonEmoji.checked = false
                    input.forceActiveFocus()
                }
            }
        }
    }
}
