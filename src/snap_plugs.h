/**
 * SPDX-FileCopyrightText: 2024 Soumyadeep Ghosh <soumyadeepghosh2004@zohomail.in>
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#pragma once
#include <KQuickConfigModule>
#include <QList>
#include <QObject>
#include <Snapd/Client>
#include <qtmetamacros.h>
#include "kcm_snap.h"

class SnapPermissions : public KQuickConfigModule
{
    Q_OBJECT

    public:
        SnapPermissions(QObject *parent, const KPluginMetaData &data);
        Q_INVOKABLE const QList<KCMSnap>& snaps() const;

    private:
        QSnapdClient m_client;
        QList<KCMSnap> m_snaps;
};