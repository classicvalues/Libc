/*
 * Copyright (c) 1999 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * Copyright (c) 1999-2003 Apple Computer, Inc.  All Rights Reserved.
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */
/*
 * catch_exception_raise_state_identity will be implemented by user programs
 * This implementation is provided to resolve the reference in
 * exc_server().
 */

#include <mach/boolean.h>
#include <mach/message.h>
#include <mach/exception.h>
#include <mach/mig_errors.h>
#include <mach-o/dyld.h>
#include <stdlib.h>

__private_extern__ kern_return_t internal_catch_exception_raise_state_identity (
        mach_port_t exception_port,
        mach_port_t thread,
        mach_port_t task,
        exception_type_t exception,
        exception_data_t code,
        mach_msg_type_number_t codeCnt,
        int *flavor,
        thread_state_t old_state,
        mach_msg_type_number_t old_stateCnt,
        thread_state_t new_state,
        mach_msg_type_number_t *new_stateCnt)
{
#if defined(__DYNAMIC__)
    static int checkForFunction = 0;
    /* This will be non-zero if the user has defined this function */
    static kern_return_t (*func)(mach_port_t, mach_port_t, mach_port_t, exception_type_t, exception_data_t, mach_msg_type_number_t, int *, thread_state_t, mach_msg_type_number_t, thread_state_t, mach_msg_type_number_t *);
    if (checkForFunction == 0) {
        checkForFunction = 1;
        _dyld_lookup_and_bind("_catch_exception_raise_state_identity", (unsigned long *)&func, (void **)0);
    }
    if (func == 0) {
        /* The user hasn't defined catch_exception_raise in their binary */
        abort();
    }
    return (*func)(exception_port, thread, task, exception, code, codeCnt, flavor, old_state, old_stateCnt, new_state, new_stateCnt);
#else
    extern kern_return_t catch_exception_raise_state_identity(mach_port_t, mach_port_t, mach_port_t, exception_type_t, exception_data_t, mach_msg_type_number_t, int *, thread_state_t, mach_msg_type_number_t, thread_state_t, mach_msg_type_number_t *);
    return catch_exception_raise_state_identity(exception_port, thread, task, exception, code, codeCnt, flavor, old_state, old_stateCnt, new_state, new_stateCnt);
#endif
}
