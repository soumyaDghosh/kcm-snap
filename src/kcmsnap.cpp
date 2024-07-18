#include "kcmsnap.h"
 
KCMSnap::KCMSnap(QSnapdSnap* &snap, const QList<QSnapdPlug*> &plugs, const QList<QSnapdSlot*> &slots)
    : m_snap(snap), 
    m_plugs(plugs), 
    m_slots(slots)
{

}
 
QSnapdSnap* KCMSnap::snap() const 
{ 
    return m_snap; 
}
 
const QList<QSnapdPlug*>& KCMSnap::plugs() const 
{ 
    return m_plugs; 
}
 
const QList<QSnapdSlot*>& KCMSnap::slots() const 
{ 
    return m_slots; 
}