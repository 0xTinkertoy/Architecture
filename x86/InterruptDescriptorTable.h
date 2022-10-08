//
//  InterruptDescriptorTable.h
//  Kernel-x86
//
//  Created by FireWolf on 8/15/20.
//  Copyright © 2020 FireWolf. All rights reserved.
//

#ifndef InterruptDescriptorTable_h
#define InterruptDescriptorTable_h

#include <Types.hpp>

#ifdef __cplusplus
extern "C" {
#endif

/// Initialize the Global Descriptor Table
void IDTInitialize(void);

///
/// Set the handler for a hardware interrupt
///
/// @param interrupt The interrupt number
/// @param handler Address of the handler
///
void IDTSetInterruptHandler(UInt32 interrupt, UInt32 handler);

///
/// Set the handler for a trap
///
/// @param trap The trap number
/// @param handler Address of the handler
///
void IDTSetTrapHandler(UInt32 trap, UInt32 handler);

#ifdef __cplusplus
}
#endif

#endif /* InterruptDescriptorTable_h */
