//
//  Context.h
//  Kernel-ARM
//
//  Created by FireWolf on 2/4/21.
//

#ifndef Context_h
#define Context_h

#include <Types.hpp>
#include <cstdarg>

///
/// Stack frame when the processor is interrupted
///
/// @note The ARM Cortex-M processor automatically pushes these registers onto the current active stack
///       e.g. If a user process is running in Unprivileged Thread Mode with the Process Stack (SP_proc),
///            then registers are pushed on the process stack.
struct Context
{
    // Low Address: Stack Top
    // Callee-saved registers
    UInt32 r4;

    UInt32 r5;

    UInt32 r6;

    UInt32 r7;

    UInt32 r8;

    UInt32 r9;

    UInt32 r10;

    UInt32 r11;

    // Caller-saved registers
    // (Saved by the processor)
    UInt32 r0;

    UInt32 r1;

    UInt32 r2;

    UInt32 r3;

    UInt32 r12;

    // The return address
    UInt32 r14;

    // The program counter, same as EIP in x86
    UInt32 r15;

    // The program status register
    UInt32 xpsr;

    UInt32 getSyscallIdentifier()
    {
        return this->r0;
    }

    va_list* getSyscallArgumentList()
    {
        return reinterpret_cast<va_list*>(this->r1);
    }

    void setSyscallKernelReturnValue(int krv)
    {
        this->r0 = krv;
    }
};

#endif /* Context_h */
