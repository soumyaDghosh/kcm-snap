/**
 * SPDX-FileCopyrightText: Year Author <author@domain.com>
 * SPDX-License-Identifier: GPL-2.0-or-later
 */


import QtQuick
import QtQuick.Controls as Controls

import org.kde.kirigami as Kirigami
import org.kde.kcmutils as KCMUtils
import org.kde.plasma.kcm.snappermissions

KCMUtils.ScrollViewKCM {
    id: root
    required property SnapPermissions perm: SnapPermissions{};

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

}
