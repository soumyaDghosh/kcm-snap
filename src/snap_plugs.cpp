/**
 * SPDX-FileCopyrightText: Year Author <author@domain.com>
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "snap_plugs.h"
#include <Snapd/Enums>
#include <Snapd/Plug>
#include <Snapd/Request>
#include <Snapd/Snap>
#include <Snapd/Slot>

K_PLUGIN_CLASS_WITH_JSON(SnapPermissions, "snap_kcm.json")

void handleFetchedSnaps(QSnapdGetSnapsRequest* req, QList<QSnapdSnap*>& snaps)
{
    qDebug() << "Fetched the snaps....";
    if(req) 
    {
        for (int i = 0; i < req->snapCount(); ++i) 
        {
            snaps.append(req->snap(i));
        }
    }
}

void handleFetchedConnections(QSnapdGetConnectionsRequest* req, QList<QSnapdPlug*>& plugs, QList<QSnapdSlot*>& slots)
{
    qDebug() << "Fetched the connections....";
    if (req) 
    {
        for (int i = 0; i < req->plugCount(); ++i) 
        {
            plugs.append(req->plug(i));
        }
        for (int i = 0; i < req->slotCount(); ++i)
        {
            slots.append(req->slot(i));
        }
    }
}

SnapPermissions::SnapPermissions(QObject *parent, const KPluginMetaData &data)
    : KQuickConfigModule{ parent, data },
    m_client{ new QSnapdClient }
{
    constexpr const char *uri = "org.kde.plasma.kcm.snappermissions";
    qmlRegisterType<SnapPermissions>(uri, 1, 0, "SnapPermissions");
    QList<QSnapdSnap*> loadedSnaps;
    QList<QSnapdPlug*> loadedPlugs;
    QList<QSnapdSlot*> loadedSlots;
    QSnapdGetSnapsRequest* reqGetSnaps{ m_client->getSnaps() };
    QSnapdGetConnectionsRequest* reqGetConnections{ m_client->getConnections() };
    reqGetSnaps->runSync();
    handleFetchedSnaps(reqGetSnaps, loadedSnaps);
    reqGetConnections->runSync();
    handleFetchedConnections(reqGetConnections, loadedPlugs, loadedSlots);
    qDebug() << "Setting Snap";
    for (QSnapdSnap* snap : loadedSnaps) 
    {
        QList<QSnapdPlug*> plugsForSnap;
        QList<QSnapdSlot*> slotsForSnap;
        for (QSnapdPlug* plug : plugsForSnap)
        {
            if (plug->snap() == snap->name()) 
            {
                plugsForSnap.append(plug);
            }
        }
        for (QSnapdSlot* slot : slotsForSnap) 
        {
            if (slot->snap() == snap->name()) 
            {
                slotsForSnap.append(slot);
            }
        }
        m_snaps.append(KCMSnap{ snap, plugsForSnap, slotsForSnap });
    }
    snaps();
}

const QList<KCMSnap>& SnapPermissions::snaps() const
{
    for (auto temp : m_snaps) {
        qDebug() << temp.snap()->name();
    }
    return m_snaps;
}

#include "snap_plugs.moc"