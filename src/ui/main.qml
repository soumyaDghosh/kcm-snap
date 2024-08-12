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

    title: i18n("Permissions")
    implicitWidth: Kirigami.Units.gridUnit * 15
    framedView: false

        Kirigami.PlaceholderMessage {
            text: i18n("Select an application from the list to view its permissions here")
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
            delegate: QQC2.ItemDelegate {
                required property var modelData

                id: delegate
                text: modelData.title
                
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
                    console.log(modelData.plugs)
                    console.log(modelData.slots)
                    overlay.open()
                }
                Kirigami.OverlaySheet {
                    id: overlay
                    title: "Plugs"
                    ListView {
                        id: overlayView
                        model: modelData.plugs
                        delegate: QQC2.ItemDelegate {
                            id: smallDelegate
                        }
                    }
                }
            }
        }
}
