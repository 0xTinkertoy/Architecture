//
//  GlobalDescriptorTable.c
//  Kernel-x86
//
//  Created by FireWolf on 8/15/20.
//  Copyright © 2020 FireWolf. All rights reserved.
//

#include "GlobalDescriptorTable.h"
#include "SegmentDescriptor.h"
#include "i386.h"

/// The Global Descriptor Table (for a single CPU)
#define kGDTNumEntries 8
struct SegmentDescriptor gGDT[kGDTNumEntries];

/// Represents the content of a GDT register
struct GDTR
{
    /// Size of the table in bytes - 1
    UInt32 length: 16;
    
    /// Address of the table
    UInt32 address: 32;
    
    /// Unused 16 bits
    UInt32 unused: 16;
} __attribute__((packed));

///
/// Load the Global Descriptor Table
///
/// @param table The table to be loaded
/// @param count Number of segments defined in the table
///
static inline void GDTLoad(struct SegmentDescriptor* table, UInt32 count)
{
    struct GDTR gdtr;
    
    gdtr.length = count * sizeof(struct SegmentDescriptor) - 1;
    
    gdtr.address = (UInt32) table;
    
    asm volatile("lgdt (%[gdtr])"
                 :
                 : [gdtr] "r" (&gdtr)
                 :
                 );
}

/// Initialize the Global Descriptor Table
void GDTInitialize(void)
{
    //memset(gGDT, 0, kGDTNumEntries * sizeof(struct SegmentDescriptor));
    
    SegmentDescriptorInitializeCodeSegment(&gGDT[kKernCodeSegment], 0x0, 0xFFFFFFFF, kKernPrivilegeLevel);
    
    SegmentDescriptorInitializeDataSegment(&gGDT[kKernDataSegment], 0x0, 0xFFFFFFFF, kKernPrivilegeLevel);
    
    SegmentDescriptorInitializeCodeSegment(&gGDT[kUserCodeSegment], 0x0, 0xFFFFFFFF, kUserPrivilegeLevel);
    
    SegmentDescriptorInitializeDataSegment(&gGDT[kUserDataSegment], 0x0, 0xFFFFFFFF, kUserPrivilegeLevel);
    
    GDTLoad(gGDT, kGDTNumEntries);
}
