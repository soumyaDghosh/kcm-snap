# SPDX-FileCopyrightText: Year Author <email@company.com>
#
# SPDX-License-Identifier: BSD-2-Clause

kcmutils_add_qml_kcm(snap_kcm)
target_sources(snap_kcm PRIVATE
   snappermissions.cpp
   snappermissions.h
   kcmsnap.cpp
   kcmsnap.h
)
target_link_libraries(snap_kcm PRIVATE
    Qt::Quick
    KF6::CoreAddons
    KF6::KCMUtils
    KF6::I18n
    Snapd::Core
)