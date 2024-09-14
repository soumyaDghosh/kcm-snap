/**
 * SPDX-FileCopyrightText: Year Author <author@domain.com>
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "snappermissions.h"
#include <Snapd/Enums>
#include <Snapd/Plug>
#include <Snapd/Request>
#include <Snapd/Snap>
#include <Snapd/Slot>

K_PLUGIN_CLASS_WITH_JSON(SnapPermissions, "kcm_snap.json")

SnapPermissions::SnapPermissions(QObject *parent, const KPluginMetaData &data)
    : KQuickConfigModule{ parent, data }
    , snap_model(new SnapBackend())
{
    constexpr const char *uri = "org.kde.plasma.kcm.snappermissions";
    qmlRegisterType<SnapBackend>(uri, 1, 0, "SnapBackend");
    setButtons(NoAdditionalButton);
}

#include "snappermissions.moc"