//////////////////////////////////////////////////////////////////////////////
// Product: QK/C++
// Last Updated for Version: 4.3.00
// Date of the Last Update:  Nov 02, 2011
//
//                    Q u a n t u m     L e a P s
//                    ---------------------------
//                    innovating embedded systems
//
// Copyright (C) 2002-2011 Quantum Leaps, LLC. All rights reserved.
//
// This software may be distributed and modified under the terms of the GNU
// General Public License version 2 (GPL) as published by the Free Software
// Foundation and appearing in the file GPL.TXT included in the packaging of
// this file. Please note that GPL Section 2[b] requires that all works based
// on this software must also be made publicly available under the terms of
// the GPL ("Copyleft").
//
// Alternatively, this software may be distributed and modified under the
// terms of Quantum Leaps commercial licenses, which expressly supersede
// the GPL and are specifically designed for licensees interested in
// retaining the proprietary status of their code.
//
// Contact information:
// Quantum Leaps Web site:  http://www.quantum-leaps.com
// e-mail:                  info@quantum-leaps.com
//////////////////////////////////////////////////////////////////////////////
#include "qk_pkg.h"
//#include "qassert.h"

/// \file
/// \ingroup qk
/// \brief QK::mutexLock()/QK::mutexUnlock() implementation.

#ifdef QK_NO_MUTEX
    #error "qk_mutex.cpp included in the build when QK_NO_MUTEX defined"
#endif

#ifdef Q_USE_NAMESPACE
namespace QP {
#endif

//Q_DEFINE_THIS_MODULE(qk_mutex)

// package-scope objects -----------------------------------------------------
uint8_t volatile QK_ceilingPrio_;               // ceiling priority of a mutex

//............................................................................
QMutex QK::mutexLock(uint8_t prioCeiling) {
    QF_CRIT_STAT_
    QF_CRIT_ENTRY_();
    uint8_t mutex = QK_ceilingPrio_; // original QK priority ceiling to return
    if (QK_ceilingPrio_ < prioCeiling) {
        QK_ceilingPrio_ = prioCeiling;        // raise the QK priority ceiling
    }

    QS_BEGIN_NOCRIT_(QS_QK_MUTEX_LOCK, (void *)0, (void *)0)
        QS_TIME_();                                               // timestamp
        QS_U8_(mutex);                                // the original priority
        QS_U8_(QK_ceilingPrio_);               // the current priority ceiling
    QS_END_NOCRIT_()

    QF_CRIT_EXIT_();
    return mutex;
}
//............................................................................
void QK::mutexUnlock(QMutex mutex) {
    QF_CRIT_STAT_
    QF_CRIT_ENTRY_();

    QS_BEGIN_NOCRIT_(QS_QK_MUTEX_UNLOCK, (void *)0, (void *)0)
        QS_TIME_();                                               // timestamp
        QS_U8_(mutex);                                // the original priority
        QS_U8_(QK_ceilingPrio_);               // the current priority ceiling
    QS_END_NOCRIT_()

    if (QK_ceilingPrio_ > mutex) {
        QK_ceilingPrio_ = mutex;         // restore the saved priority ceiling
        mutex = QK_schedPrio_();             // reuse 'mutex' to hold priority
        if (mutex != (uint8_t)0) {
            QK_sched_(mutex);
        }
    }
    QF_CRIT_EXIT_();
}

#ifdef Q_USE_NAMESPACE
}                                                              // namespace QP
#endif
