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

K_PLUGIN_CLASS_WITH_JSON(SnapPermissions, "snap_kcm.json")

SnapPermissions::SnapPermissions(QObject *parent, const KPluginMetaData &data)
    : KQuickConfigModule{ parent, data },
    m_client{ this }
{
    qmlRegisterType<SnapPermissions>("org.kde.plasma.kcm.snappermissions", 1, 0, "SnapPermissions");
    //Initalize locals
    QList<QSnapdSnap*> loadedSnaps;
    QList<QSnapdPlug*> loadedPlugs;
    QList<QSnapdSlot*> loadedSlots;
    QSnapdGetSnapsRequest* reqGetSnaps{ m_client.getSnaps() };
    QSnapdGetConnectionsRequest* reqGetConnections{ m_client.getConnections() };
    //Fetch snaps
    if(reqGetSnaps) 
    {
        reqGetSnaps->runSync();
        for (int i = 0; i < reqGetSnaps->snapCount(); ++i) 
        {
            loadedSnaps.append(reqGetSnaps->snap(i));
        }
    }
    //Fetch connections
    if (reqGetConnections) 
    {
        reqGetConnections->runSync();
        for (int i = 0; i < reqGetConnections->plugCount(); ++i) 
        {
            loadedPlugs.append(reqGetConnections->plug(i));
        }
        for (int i = 0; i < reqGetConnections->slotCount(); ++i)
        {
            loadedSlots.append(reqGetConnections->slot(i));
        }
    }
    //Get snaps and their associated plugs and slots
    for (QSnapdSnap* snap : loadedSnaps) 
    {
        QList<QSnapdPlug*> plugsForSnap;
        QList<QSnapdSlot*> slotsForSnap;
        for (QSnapdPlug* plug : loadedPlugs)
        {
            if (plug->snap() == snap->name()) 
            {
                plugsForSnap.append(plug);
            }
        }
        for (QSnapdSlot* slot : loadedSlots) 
        {
            if (slot->snap() == snap->name()) 
            {
                slotsForSnap.append(slot);
            }
        }
        m_snaps.append(KCMSnap{ snap, plugsForSnap, slotsForSnap });
    }
    //Print results
    for (const KCMSnap& snap : m_snaps) 
    {
        qDebug() << snap.snap()->name();
    }
}

const QList<KCMSnap>& SnapPermissions::snaps() const
{
    return m_snaps;
}

#include "snap_plugs.moc"