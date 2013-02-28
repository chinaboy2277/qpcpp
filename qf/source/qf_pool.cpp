//////////////////////////////////////////////////////////////////////////////
// Product: QF/C++
// Last Updated for Version: 4.2.00
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
#include "qf_pkg.h"
#include "qassert.h"

/// \file
/// \ingroup qf
/// \brief QF_pool_[] and QF_maxPool_ definition, QF::poolInit()
/// implementation.

#ifdef Q_USE_NAMESPACE
namespace QP {
#endif

Q_DEFINE_THIS_MODULE(qf_pool)

// Package-scope objects -----------------------------------------------------
QF_EPOOL_TYPE_ QF_pool_[QF_MAX_EPOOL];             // allocate the event pools
uint8_t QF_maxPool_;                      // number of initialized event pools

//............................................................................
void QF::poolInit(void *poolSto, uint32_t poolSize, QEventSize evtSize) {
                         // cannot exceed the number of available memory pools
    Q_REQUIRE(QF_maxPool_ < (uint8_t)Q_DIM(QF_pool_));
               // please initialize event pools in ascending order of evtSize:
    Q_REQUIRE((QF_maxPool_ == (uint8_t)0)
              || (QF_EPOOL_EVENT_SIZE_(QF_pool_[QF_maxPool_ - 1]) < evtSize));
    QF_EPOOL_INIT_(QF_pool_[QF_maxPool_], poolSto, poolSize, evtSize);
    ++QF_maxPool_;                                            // one more pool
}

#ifdef Q_USE_NAMESPACE
}                                                              // namespace QP
#endif

