/**
 * SPDX-FileCopyrightText: Year Author <author@domain.com>
 * SPDX-License-Identifier: GPL-2.0-or-later
 */


import QtQuick
import QtQuick.Layouts
import QtQuick.Controls as QQC2

import org.kde.kirigami as Kirigami
import org.kde.kirigami.delegates as KD
import org.kde.kcmutils as KCMUtils
import org.kde.plasma.kcm.snappermissions 1.0

KCMUtils.ScrollViewKCM {
    SnapBackend {
        id: backendInstance
    }
    id: root
    property SnapBackend perm: backendInstance
    property var output

    title: i18n("Permissions")
    implicitWidth: Kirigami.Units.gridUnit * 15
    framedView: false

    Kirigami.PlaceholderMessage {
        text: i18n("Install snaps to change the.")
        width: parent.width - (Kirigami.Units.largeSpacing * 4)
        anchors.centerIn: parent
        visible: perm === null
    }

    Kirigami.Separator {
        anchors.left: parent.left
        height: parent.height
    }

    ListView {
        anchors.fill: parent
        id: view
        model: root.perm.snaps
        spacing: Kirigami.Units.LargeSpacing
        delegate: QQC2.ItemDelegate {
            required property var modelData
            property string snapTitle: modelData.title
            id: delegate
            text: snapTitle
            width: ListView.view.width
            contentItem: RowLayout {
                spacing: Kirigami.Units.smallSpacing
                KD.TitleSubtitle {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    title: delegate.text
                    selected: delegate.highlighted
                    font: delegate.font
                }
            }
            onClicked: {
                overlay.open()
            }
            
            Kirigami.OverlaySheet {
                id: overlay
                parent: view.QQC2.Overlay.overlay
                width: view.width / 2
                title: i18n("Plugs for %1").arg(modelData.title)

                ListView {
                    id: overlayView
                    model: modelData.plugs
                    anchors.fill: parent
                    delegate: QQC2.SwitchDelegate {
                        property string plugName: modelData.name
                        property int plugCount: modelData.connectedSlotCount
                        property string slotInterface: modelData.interface
                        property string plugSnap: modelData.snap
                        id: smallDelegate
                        text: plugName
                        width: ListView.view.width
                        checked: plugCount === 1 || modelData.checked === true
                        onClicked: {
                            var originalState = checked;
                            if (checked) {
                                output = root.perm.connectPlug(plugSnap, plugName, "snapd", slotInterface);
                            } 
                            if (!checked) {
                                output = root.perm.disconnectPlug(plugSnap, plugName, "snapd", slotInterface);
                            }
                            
                            if (output !== "") {
                                errorOverlay.open();
                                toggle();
                            }
                        }
                    }
                }
            }
        }
    }

    // Error Overlay Definition
    Kirigami.OverlaySheet {
        id: errorOverlay
        property bool copyButtonEnabled: true
        parent: view.QQC2.Overlay.overlay
        width: view.width / 2
        title: i18n("Error")
        visible: success !== ""
        bottomPadding: 10

        Kirigami.FormLayout {
            QQC2.Label {
                Kirigami.FormData.label: ""
                text: "snapd error: " + output // Display the error string
                textFormat: Text.StyledText
                wrapMode: Text.Wrap
            }
        }
    }
}
