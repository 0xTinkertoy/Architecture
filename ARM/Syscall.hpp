//
//  Syscall.hpp
//  Kernel-ARM
//
//  Created by FireWolf on 2/4/21.
//

#ifndef ARMSyscall_hpp
#define ARMSyscall_hpp

///
/// Invoke a system call
///
/// @param call The system call identifier
/// @param ... Zero or more arguments
/// @return The kernel return value.
///
extern "C" int syscall(int call, ...);

#endif /* ARMSyscall_hpp */
