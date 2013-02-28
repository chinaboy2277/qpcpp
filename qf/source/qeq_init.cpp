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

/// \file
/// \ingroup qf
/// \brief QEQueue::init() implementation.

#ifdef Q_USE_NAMESPACE
namespace QP {
#endif

//............................................................................
void QEQueue::init(QEvent const *qSto[], QEQueueCtr qLen) {
    m_frontEvt = (QEvent *)0;                        // no events in the queue
    m_ring     = &qSto[0];
    m_end      = qLen;
    m_head     = (QEQueueCtr)0;
    m_tail     = (QEQueueCtr)0;
    m_nFree    = qLen;
    m_nMin     = qLen;

    QS_CRIT_STAT_
    QS_BEGIN_(QS_QF_EQUEUE_INIT, QS::eqObj_, this)
        QS_OBJ_(qSto);                                  // this QEQueue object
        QS_EQC_(qLen);                              // the length of the queue
    QS_END_()
}

#ifdef Q_USE_NAMESPACE
}                                                              // namespace QP
#endif
