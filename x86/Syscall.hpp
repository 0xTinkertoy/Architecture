//
//  Syscall.hpp
//  Kernel-x86
//
//  Created by FireWolf on 2/4/21.
//

#ifndef X86Syscall_hpp
#define X86Syscall_hpp

///
/// Invoke a system call
///
/// @param call The system call identifier
/// @param ... Zero or more arguments
/// @return The kernel return value.
///
extern "C" int syscall(int call, ...);

#endif /* X86Syscall_hpp */
