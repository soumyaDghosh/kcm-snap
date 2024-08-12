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
        static bool comparebyName(QSnapdSnap*, QSnapdSnap*);
    
    Q_SIGNALS:
        void snapsChanged();

    private:
        QSnapdClient m_client;
        QList<KCMSnap *> m_snaps;
};