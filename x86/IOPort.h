//
//  IOPort.h
//  Kernel-x86
//
//  Created by FireWolf on 8/14/20.
//  Copyright © 2020 FireWolf. All rights reserved.
//

#ifndef IOPort_h
#define IOPort_h

#include <Types.hpp>

// MARK: Read from an I/O port

///
/// Read a byte from the given I/O port
///
/// @param port An I/O port
/// @return The byte value.
///
static inline UInt8 IOPortRead8(UInt16 port)
{
    UInt8 data;
    
    asm volatile("in %[port], %[data]"
                 // Output Operands
                 // [ASMSymbolicName] Constraint (CVariableName)
                 // "=" indicates that the output variable can be overwritten;
                 // "a" indicates that the output variable is stored in %al.
                 : [data] "=a" (data)
                 //  Input Operands
                 // "d" indicates that the input variable is stored in %dx.
                 : [port] "d" (port)
                 :
                 );
    
    return data;
}

///
/// Read a word from the given I/O port
///
/// @param port An I/O port
/// @return The word value.
///
static inline UInt16 IOPortRead16(UInt16 port)
{
    UInt16 data;
    
    asm volatile("in %[port], %[data]"
                 : [data] "=a" (data)
                 : [port] "d" (port)
                 :
                 );
    
    return data;
}

///
/// Read a double word from the given I/O port
///
/// @param port An I/O port
/// @return The double word value.
///
static inline UInt32 IOPortRead32(UInt16 port)
{
    UInt32 data;
    
    asm volatile("in %[port], %[data]"
                 : [data] "=a" (data)
                 : [port] "d" (port)
                 :
                 );
    
    return data;
}

///
/// Read multiple bytes from the given I/O port
///
/// @param port An I/O port
/// @param dst The destination buffer that stores the bytes
/// @param count The number of bytes to read from the port
/// @ref https://c9x.me/x86/html/file_module_x86_id_141.html
/// @ref https://c9x.me/x86/html/file_module_x86_id_279.html
///
static inline void IOPortRead8s(UInt16 port, void* dst, size_t count)
{
    //     ins: Port specified in %dx while memory location in %edi
    // rep ins: Read %ecx bytes from the port %dx into the memory %edi
    asm volatile("cld; rep insb"
                 // Output Operands
                 // `count` will be decremented until 0 to terminate the operation
                 : "=D" (dst), "=c" (count)
                 // Input Operands
                 // "0" indicates that `dst` must be in the same place as specified by the first entry in the output list
                 // The same concept applies to "1"
                 : "d" (port), "0" (dst), "1" (count)
                 // Clobbers
                 // "memory" indicates that the memory will be modified;
                 // "cc" indicates that flags will be modified.
                 : "memory", "cc"
                 );
}

///
/// Read multiple words from the given I/O port
///
/// @param port An I/O port
/// @param dst The destination buffer that stores the bytes
/// @param count The number of bytes to read from the port
/// @ref https://c9x.me/x86/html/file_module_x86_id_141.html
/// @ref https://c9x.me/x86/html/file_module_x86_id_279.html
///
static inline void IOPortRead16s(UInt16 port, void* dst, size_t count)
{
    //     ins: Port specified in %dx while memory location in %edi
    // rep ins: Read %ecx bytes from the port %dx into the memory %edi
    asm volatile("cld; rep insw"
                 // Output Operands
                 // `count` will be decremented until 0 to terminate the operation
                 : "=D" (dst), "=c" (count)
                 // Input Operands
                 // "0" indicates that `dst` must be in the same place as specified by the first entry in the output list
                 // The same concept applies to "1"
                 : "d" (port), "0" (dst), "1" (count)
                 // Clobbers
                 // "memory" indicates that the memory will be modified;
                 // "cc" indicates that flags will be modified.
                 : "memory", "cc"
                 );
}

///
/// Read multiple double words from the given I/O port
///
/// @param port An I/O port
/// @param dst The destination buffer that stores the bytes
/// @param count The number of bytes to read from the port
/// @ref https://c9x.me/x86/html/file_module_x86_id_141.html
/// @ref https://c9x.me/x86/html/file_module_x86_id_279.html
///
static inline void IOPortRead32s(UInt16 port, void* dst, size_t count)
{
    //     ins: Port specified in %dx while memory location in %edi
    // rep ins: Read %ecx bytes from the port %dx into the memory %edi
    asm volatile("cld; rep insd"
                 // Output Operands
                 // `count` will be decremented until 0 to terminate the operation
                 : "=D" (dst), "=c" (count)
                 // Input Operands
                 // "0" indicates that `dst` must be in the same place as specified by the first entry in the output list
                 // The same concept applies to "1"
                 : "d" (port), "0" (dst), "1" (count)
                 // Clobbers
                 // "memory" indicates that the memory will be modified;
                 // "cc" indicates that flags will be modified.
                 : "memory", "cc"
                 );
}

// MARK: Write to an I/O port

///
/// Write a byte to the given I/O port
///
/// @param port An I/O port
/// @param data The byte value
///
static inline void IOPortWrite8(UInt16 port, UInt8 data)
{
    asm volatile("out %[data], %[port]"
                 :
                 : [data] "a" (data), [port] "d" (port)
                 :
                 );
}

///
/// Write a word to the given I/O port
///
/// @param port An I/O port
/// @param data The word value
///
static inline void IOPortWrite16(UInt16 port, UInt16 data)
{
    asm volatile("out %[data], %[port]"
                 :
                 : [data] "a" (data), [port] "d" (port)
                 :
                 );
}

///
/// Write a double word to the given I/O port
///
/// @param port An I/O port
/// @param data The double word value
///
static inline void IOPortWrite32(UInt16 port, UInt32 data)
{
    asm volatile("out %[data], %[port]"
                 :
                 : [data] "a" (data), [port] "d" (port)
                 :
                 );
}

///
/// Write mulitple bytes to the given I/O port
///
/// @param port An I/O port
/// @param src The source buffer that stores the bytes
/// @param count The number of bytes to write to the port
/// @ref https://c9x.me/x86/html/file_module_x86_id_223.html
/// @ref https://c9x.me/x86/html/file_module_x86_id_279.html
///
static inline void IOPortWrite8s(UInt16 port, const void* src, size_t count)
{
    //     outs: Port specified in %dx while memory location in %esi
    // rep outs: Write %ecx bytes from the memory %esi to the port %dx
    asm volatile("cld; rep outsb"
                 : "=S" (src), "=c" (count)
                 : "d" (port), "0" (src), "1" (count)
                 : "cc"
                 );
}

///
/// Write mulitple words to the given I/O port
///
/// @param port An I/O port
/// @param src The source buffer that stores the bytes
/// @param count The number of bytes to write to the port
/// @ref https://c9x.me/x86/html/file_module_x86_id_223.html
/// @ref https://c9x.me/x86/html/file_module_x86_id_279.html
///
static inline void IOPortWrite16s(UInt16 port, const void* src, size_t count)
{
    //     outs: Port specified in %dx while memory location in %esi
    // rep outs: Write %ecx bytes from the memory %esi to the port %dx
    asm volatile("cld; rep outsb"
                 : "=S" (src), "=c" (count)
                 : "d" (port), "0" (src), "1" (count)
                 : "cc"
                 );
}

///
/// Write mulitple double words to the given I/O port
///
/// @param port An I/O port
/// @param src The source buffer that stores the bytes
/// @param count The number of bytes to write to the port
/// @ref https://c9x.me/x86/html/file_module_x86_id_223.html
/// @ref https://c9x.me/x86/html/file_module_x86_id_279.html
///
static inline void IOPortWrite32s(UInt16 port, const void* src, size_t count)
{
    //     outs: Port specified in %dx while memory location in %esi
    // rep outs: Write %ecx bytes from the memory %esi to the port %dx
    asm volatile("cld; rep outsb"
                 : "=S" (src), "=c" (count)
                 : "d" (port), "0" (src), "1" (count)
                 : "cc"
                 );
}

#endif /* IOPort_h */
