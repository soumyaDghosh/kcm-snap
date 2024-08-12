#pragma once
#include <QList>
#include <QPointer>
#include <Snapd/Snap>
#include <Snapd/Plug>
#include <Snapd/Slot>
 
class KCMSnap : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QSnapdSnap* snap READ snap CONSTANT)
    Q_PROPERTY(QList<QSnapdPlug *> plugs READ plugs CONSTANT)
    Q_PROPERTY(QList<QSnapdSlot *> slots READ slots CONSTANT)
    Q_PROPERTY(QString title READ title CONSTANT)
    //Q_PROPERTY(QImage icon READ icon CONSTANT)

    public:
        KCMSnap(QSnapdSnap* snap, const QList<QSnapdPlug*> plugs, const QList<QSnapdSlot*> slots);
        QSnapdSnap* snap() const;
        const QList<QSnapdPlug*> plugs() const;
        const QList<QSnapdSlot*> slots() const;
        const QString title() const;
        //QImage icon() const;
 
    private:
        QSnapdSnap* m_snap;
        QList<QSnapdPlug *> m_plugs;
        QList<QSnapdSlot *> m_slots;
};