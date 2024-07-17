#pragma once
#include <QList>
#include <QPointer>
#include <Snapd/Snap>
#include <Snapd/Plug>
#include <Snapd/Slot>
 
class KCMSnap
{
    public:
        KCMSnap(QSnapdSnap* &snap, const QList<QSnapdPlug*>& plugs, const QList<QSnapdSlot*>& slots);
        QSnapdSnap* snap() const;
        const QList<QSnapdPlug*>& plugs() const;
        const QList<QSnapdSlot*>& slots() const;
 
    private:
        QPointer<QSnapdSnap> m_snap;
        QList<QSnapdPlug *> m_plugs;
        QList<QSnapdSlot *> m_slots;
};