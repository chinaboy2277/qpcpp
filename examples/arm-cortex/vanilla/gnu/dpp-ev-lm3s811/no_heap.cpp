//////////////////////////////////////////////////////////////////////////////
// Product: Dummy heap management to reduce the codesize, GCC 4.3.3
// Last Updated for Version: 4.1.02
// Date of the Last Update:  Feb 14, 2010
//
//                    Q u a n t u m     L e a P s
//                    ---------------------------
//                    innovating embedded systems
//
// Copyright (C) 2002-2010 Quantum Leaps, LLC. All rights reserved.
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

#include "qp_port.h"
#include <stdlib.h>                   // for prototypes of malloc() and free()

Q_DEFINE_THIS_FILE

//............................................................................
void *malloc(size_t) {
    Q_ERROR();
    return (void *)0;
}
//............................................................................
void free(void *) {
    Q_ERROR();
}
//............................................................................
void *calloc(size_t, size_t) {
    Q_ERROR();
    return (void *)0;
}