# SPDX-FileCopyrightText: Year Author <email@company.com>
#
# SPDX-License-Identifier: BSD-2-Clause

kcmutils_add_qml_kcm(snap_kcm)
target_sources(snap_kcm PRIVATE
   snap_plugs.cpp
   snap_plugs.h
   kcm_snap.cpp
   kcm_snap.h
)
target_link_libraries(snap_kcm PRIVATE
    Qt::Quick
    KF6::CoreAddons
    KF6::KCMUtils
    KF6::I18n
    Snapd::Core
)