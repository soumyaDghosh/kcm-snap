#include "snapbackend.h"
#include <QtQml>

SnapBackend::SnapBackend(QObject *parent){
    //Initalize locals
    QList<QSnapdSnap*> loadedSnaps;
    QList<QSnapdPlug*> loadedPlugs;
    QList<QSnapdSlot*> loadedSlots;
    QSnapdGetSnapsRequest* reqGetSnaps{ m_client.getSnaps() };
    QSnapdGetConnectionsRequest* reqGetConnections{ m_client.getConnections(QSnapdClient::GetConnectionsFlag::SelectAll) };

    //Fetch snaps
    if(reqGetSnaps) 
    {
        reqGetSnaps->runSync();
        for (int i = 0; i < reqGetSnaps->snapCount(); ++i) 
        {
            if (reqGetSnaps->snap(i)->appCount() != 0 && reqGetSnaps->snap(i)->confinement() != QSnapdEnums::SnapConfinementClassic) {
                loadedSnaps.append(reqGetSnaps->snap(i));
            }
        }
        std::sort(loadedSnaps.begin(), loadedSnaps.end(), SnapBackend::comparebyName);
        
        Q_EMIT snapsChanged();
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
            if (plug->snap() == snap->name() && !(plug->hasAttribute(QStringLiteral("content"))))
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
        m_snaps.append(new KCMSnap(snap, plugsForSnap, slotsForSnap));
    }
    //Print results
}


const QList<KCMSnap *> SnapBackend::snaps() const
{
    return m_snaps;
}

// const QList<KCMSnap *> SnapBackend::slotSnaps() const
// {
//     return m_slotSnaps;
// }

QString SnapBackend::connectPlug(const QString &plug_snap,const QString & plug_name, const QString &slot_snap, const QString &slot_name) const
{
    QSnapdClient client;
    QSnapdConnectInterfaceRequest *req = client.connectInterface(plug_snap, plug_name, slot_snap, slot_name);
    req->runSync();
    if (req->error() != QSnapdRequest::NoError) {
        return req->errorString();
    }
    return QString();
}

QString SnapBackend::disconnectPlug(const QString &plug_snap,const QString & plug_name, const QString &slot_snap, const QString &slot_name) const
{
    QSnapdClient client;
    QSnapdDisconnectInterfaceRequest *req = client.disconnectInterface(plug_snap, plug_name, slot_snap, slot_name);
    req->runSync();
    if (req->error() != QSnapdRequest::NoError) {
        return req->errorString();
    }
    return QString();
}

bool SnapBackend::comparebyName(QSnapdSnap* a, QSnapdSnap* b) {
    return a->name() < b->name();
}