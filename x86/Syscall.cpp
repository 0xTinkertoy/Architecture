//
//  Syscall.cpp
//  Kernel-x86
//
//  Created by FireWolf on 2/4/21.
//

#include "Syscall.hpp"
#include <cstdarg>

///
/// Invoke a system call
///
/// @param call The system call identifier
/// @param ... Zero or more arguments
/// @return The kernel return value.
///
int syscall(int call, ...)
{
    // System call result
    int result = 0;

    // System call arguments
    va_list args;

    va_start(args, call);

    asm volatile("int $255"
                // Output operands
                : [result] "=a" (result)
                // Input Operands
                : [call] "a" (call), [args] "d" (args)
                :
                );

    // Deallocate the list
    va_end(args);

    return result;
}