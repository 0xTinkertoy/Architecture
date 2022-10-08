//
//  Context.h
//  Kernel-x86
//
//  Created by FireWolf on 2/4/21.
//

#ifndef Context_h
#define Context_h

#include <Types.hpp>

/// Stack frame when the processor is interrupted without a privilege level change
struct Context
{
    UInt32 edi;

    UInt32 esi;

    UInt32 ebp;

    UInt32 esp;

    UInt32 ebx;

    UInt32 edx;

    UInt32 ecx;

    UInt32 eax;

    UInt32 eip;

    UInt32 cs;

    UInt32 eflags;

    UInt32 getSyscallIdentifier()
    {
        return this->eax;
    }

    va_list* getSystemCallArgumentList()
    {
        return reinterpret_cast<va_list*>(this->edx);
    }

    void setSystemCallKernelReturnValue(int krv)
    {
        this->eax = krv;
    }
};

#endif /* Context_h */
