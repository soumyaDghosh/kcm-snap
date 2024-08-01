#include "snapbackend.h"
#include <QtQml>
#include <algorithm>

SnapBackend::SnapBackend(QObject *parent){
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
            if (reqGetSnaps->snap(i)->appCount() != 0) {
                loadedSnaps.append(reqGetSnaps->snap(i));
            }
        }
        std::sort(loadedSnaps.begin(), loadedSnaps.end(), SnapBackend::comparebyName);
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

const QList<KCMSnap>& SnapBackend::snaps() const
{
    return m_snaps;
}

bool SnapBackend::comparebyName(QSnapdSnap* a, QSnapdSnap* b) {
    return a->name() < b->name();
}