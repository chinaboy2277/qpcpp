//////////////////////////////////////////////////////////////////////////////
// Product: QEP/C++
// Last Updated for Version: 4.5.00
// Date of the Last Update:  Jul 05, 2011
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
#include "qep_pkg.h"

/// \file
/// \ingroup qep
/// \brief QHsm::isIn() implementation.

#ifdef Q_USE_NAMESPACE
namespace QP {
#endif

//............................................................................
uint8_t QHsm::isIn(QStateHandler state) {
    QStateHandler s = m_state;
    QState r;
    uint8_t inState = (uint8_t)0;    // assume that this HSM is not in 'state'
    do {
        if (m_state == state) {                        // do the states match?
            inState = (uint8_t)1;                  // match found, return TRUE
            r = Q_RET_IGNORED;                        // break out of the loop
        }
        else {
            r = QEP_TRIG_(m_state, QEP_EMPTY_SIG_);
        }
    } while (r != Q_RET_IGNORED);                // QHsm_top state not reached
    m_state = s;                                 // restore the original state
    return inState;                                       // return the status
}

#ifdef Q_USE_NAMESPACE
}                                                              // namespace QP
#endif
