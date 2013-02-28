//////////////////////////////////////////////////////////////////////////////
// Product: QF/C++
// Last Updated for Version: 4.3.00
// Date of the Last Update:  Nov 01, 2011
//
//                    Q u a n t u m     L e a P s
//                    ---------------------------
//                    innovating embedded systems
//
// Copyright (C) 2002-2008 Quantum Leaps, LLC. All rights reserved.
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
/// \brief QActive::run() implementation.

#ifdef Q_USE_NAMESPACE
namespace QP {
#endif

//............................................................................
void QActive::run(void) {
    m_running = (uint8_t)1;                    // allow the thread-loop to run
    do {
        QEvent const *e = get_();                            // wait for event
        dispatch(e);          // dispatch to the active object's state machine
        QF::gc(e);      // check if the event is garbage, and collect it if so

    } while (m_running); // loop until m_running is cleared in QActive::stop()
}

#ifdef Q_USE_NAMESPACE
}                                                              // namespace QP
#endif