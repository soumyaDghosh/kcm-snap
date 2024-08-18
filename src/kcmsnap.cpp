#include "kcmsnap.h"
 
KCMSnap::KCMSnap(QSnapdSnap* snap, const QList<QSnapdPlug*> plugs, const QList<QSnapdSlot*> slots)
    : m_snap(snap), 
    m_plugs(plugs), 
    m_slots(slots)
{}
 
QSnapdSnap* KCMSnap::snap() const 
{
    return m_snap; 
}

const QList<QSnapdPlug*> KCMSnap::plugs() const 
{
    return m_plugs; 
}
 
const QList<QSnapdSlot*> KCMSnap::slots() const 
{
    return m_slots; 
}

const QString KCMSnap::title() const
{
    QString title = m_snap->name();
    title[0] = title[0].toUpper();
    for (int i = 1; i < title.length(); ++i) {  
        if (title[i - 1] == QStringLiteral("-")) {
            title[i - 1] = QChar::Space;
            title[i] = title[i].toUpper();
        }
    }
    return title;
}

// QImage KCMSnap::icon() const
// {
//     QSnapdClient client;
//     QSnapdGetIconRequest* reqIcon = client.getIcon(m_snap->icon());
//     reqIcon->runSync();
//     QBuffer buffer;
//     buffer.setData(reqIcon->icon()->data());
//     QImageReader reader(&buffer);
//     QImage icon = reader.read();
//     return icon;
// }