#pragma once
#include "kcmsnap.h"
#include <QObject>
#include <QtQml>

#include <Snapd/Client>

class SnapBackend : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    public:
        explicit SnapBackend(QObject *parent);
        Q_INVOKABLE const QList<KCMSnap>& snaps() const;
        static bool comparebyName(QSnapdSnap*, QSnapdSnap*);
    
    private:
        QSnapdClient m_client;
        QList<KCMSnap> m_snaps;
};