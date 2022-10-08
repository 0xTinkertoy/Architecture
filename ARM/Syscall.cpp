//
//  Syscall.cpp
//  Kernel-ARM
//
//  Created by FireWolf on 2/4/21.
//

#include "Syscall.hpp"
#include <cstdarg>

int syscall(int call, ...)
{
    // System call result
    int result = 0;

    // System call arguments
    va_list args;

    va_start(args, call);

    va_list* ptr = &args;

    // We don't use the number passed to the SVC instruction to identify the system call number
    // Instead, we explicitly use argument registers to pass them to the kernel
    asm volatile("mov r0, %[call] \n"
                 "mov r1, %[aptr] \n"
                 "svc 0 \n"
                 "mov %[result], r0"
                // Output operands
                : [result] "=r" (result)
                // Input Operands
                : [call] "r" (call), [aptr] "r" (ptr)
                :
                );

    va_end(args);

    return result;
}
