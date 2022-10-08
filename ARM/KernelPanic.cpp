//
//  KernelPanic.cpp
//  Kernel-ARM
//
//  Created by FireWolf on 3/8/21.
//

#ifdef KERNEL_FORMATTED_PRINT_ENABLED

#include <Debug.hpp>

__attribute__((noreturn))
void panic(const char* format, ...)
{
    va_list args;

    va_start(args, format);

    kprintf("Kernel Panic! Reason: ");

    kvprintf(format, args);

    va_end(args);

    while (true)
    {
        asm("wfi");
    }
}

#elif not defined(KERNEL_SIMPLE_PANIC)

__attribute__((noreturn, weak))
void panic(const char* format, ...)
{
    while (true)
    {
        asm("wfi");
    }
}

#endif