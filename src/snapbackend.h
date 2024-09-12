#pragma once
#include "kcmsnap.h"
#include <QObject>
#include <QtQml>

#include <Snapd/Client>

class SnapBackend : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(QList<KCMSnap *> snaps READ snaps NOTIFY snapsChanged)

    public:
        explicit SnapBackend(QObject *parent = nullptr);
        Q_INVOKABLE const QList<KCMSnap *> snaps() const;
        //Q_INVOKABLE const QList<KCMSnap *> slotSnaps() const;
        Q_INVOKABLE QString connectPlug(const QString &plug_snap,const QString & plug_name, const QString &slot_snap, const QString &slot_name) const;
        Q_INVOKABLE QString disconnectPlug(const QString &plug_snap,const QString & plug_name, const QString &slot_snap, const QString &slot_name) const;
        static bool comparebyName(QSnapdSnap*, QSnapdSnap*);
    
    Q_SIGNALS:
        void snapsChanged();

    private:
        QSnapdClient m_client;
        QList<KCMSnap *> m_snaps;
};