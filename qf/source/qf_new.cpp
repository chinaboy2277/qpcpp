//////////////////////////////////////////////////////////////////////////////
// Product: QF/C++
// Last Updated for Version: 4.3.00
// Date of the Last Update:  Nov 01, 2011
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
#include "qf_pkg.h"
#include "qassert.h"

/// \file
/// \ingroup qf
/// \brief QF::new_() implementation.

#ifdef Q_USE_NAMESPACE
namespace QP {
#endif

Q_DEFINE_THIS_MODULE(qf_new)

//............................................................................
QEvent *QF::new_(uint16_t evtSize, QSignal sig) {
                    // find the pool id that fits the requested event size ...
    uint8_t idx = (uint8_t)0;
    while (evtSize > QF_EPOOL_EVENT_SIZE_(QF_pool_[idx])) {
        ++idx;
        Q_ASSERT(idx < QF_maxPool_);     // cannot run out of registered pools
    }

    QS_CRIT_STAT_
    QS_BEGIN_(QS_QF_NEW, (void *)0, (void *)0)
        QS_TIME_();                                               // timestamp
        QS_EVS_(evtSize);                             // the size of the event
        QS_SIG_(sig);                               // the signal of the event
    QS_END_()

    QEvent *e;
    QF_EPOOL_GET_(QF_pool_[idx], e);
    Q_ASSERT(e != (QEvent *)0);             // pool must not run out of events

    e->sig = sig;                                 // set signal for this event
    EVT_POOL_ID(e) = (uint8_t)(idx + 1);     // store the pool ID in the event
    EVT_REF_CTR(e) = (uint8_t)0;             // set the reference counter to 0

    return e;
}

#ifdef Q_USE_NAMESPACE
}                                                              // namespace QP
#endif
