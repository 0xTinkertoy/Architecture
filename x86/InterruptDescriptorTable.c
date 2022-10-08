//
//  InterruptDescriptorTable.c
//  Kernel-x86
//
//  Created by FireWolf on 8/15/20.
//  Copyright © 2020 FireWolf. All rights reserved.
//

#include "InterruptDescriptorTable.h"
#include "GateDescriptor.h"
#include "SegmentDescriptor.h"
#include "i386.h"

/// The Interrupt Descriptor Table (shared by all CPUs)
#define kIDTNumEntries 256
struct GateDescriptor gIDT[kIDTNumEntries];

/// Represents the content of a IDT register
struct IDTR
{
    /// Size of the table in bytes - 1
    UInt32 length: 16;
    
    /// Address of the table
    UInt32 address: 32;
    
    /// Unused 16 bits
    UInt32 unused: 16;
} __attribute__((packed));

///
/// Load the Interrupt Descriptor Table
///
/// @param table The table to be loaded
/// @param count Number of segments defined in the table
///
static inline void IDTLoad(struct GateDescriptor* table, UInt32 count)
{
    struct IDTR idtr;
    
    idtr.length = count * sizeof(struct GateDescriptor) - 1;
    
    idtr.address = (UInt32) table;
    
    asm volatile("lidt (%[idtr])"
                 :
                 : [idtr] "r" (&idtr)
                 :
                 );
}

/// Initialize the Global Descriptor Table
void IDTInitialize(void)
{
    //memset(gIDT, 0, kIDTNumEntries * sizeof(struct GateDescriptor));
    
    // Initialize with default handler for the first 48 entires
    extern UInt32 defevec[];

    for (int i = 0; i < 48; i += 1)
    {
        IDTSetTrapHandler(i, defevec[i]);
    }

    IDTLoad(gIDT, kIDTNumEntries);
}

///
/// Set the handler for a hardware interrupt
///
/// @param interrupt The interrupt number
/// @param handler Address of the handler
///
void IDTSetInterruptHandler(UInt32 interrupt, UInt32 handler)
{
    GateDescriptorInitializeInterruptGate(&gIDT[interrupt], kKernCodeSegment * sizeof(struct SegmentDescriptor), handler, kKernPrivilegeLevel);
}

///
/// Set the handler for a trap
///
/// @param trap The trap number
/// @param handler Address of the handler
///
void IDTSetTrapHandler(UInt32 trap, UInt32 handler)
{
    GateDescriptorInitializeTrapGate(&gIDT[trap], kKernCodeSegment * sizeof(struct SegmentDescriptor), handler, kKernPrivilegeLevel);
}
