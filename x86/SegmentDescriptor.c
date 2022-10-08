//
//  SegmentDescriptor.c
//  Kernel-x86
//
//  Created by FireWolf on 8/15/20.
//  Copyright © 2020 FireWolf. All rights reserved.
//

#include "SegmentDescriptor.h"

///
/// Initialize a 32-bit page-addressed code segment
///
/// @param descriptor The segment descriptor to be initialized
/// @param base The base address of the segment
/// @param limit The limit of the segment
/// @param privilegeLevel The privilege level of the segment
///
void SegmentDescriptorInitializeCodeSegment(struct SegmentDescriptor* descriptor, UInt32 base, UInt32 limit, UInt32 privilegeLevel)
{
    descriptor->limitL16 = limit & 0xFFFF;
    
    descriptor->baseL16 = base & 0xFFFF;
    
    descriptor->baseM8 = (base >> 16) & 0xFF;
    
    descriptor->accessed = 0;
    
    descriptor->rwaccess = 1;
    
    descriptor->dcbit = 0;
    
    descriptor->isCode = 1;
    
    descriptor->isNonSystem = 1;
    
    descriptor->privilegeLevel = privilegeLevel;
    
    descriptor->isPresent = 1;
    
    descriptor->limitH4 = (limit >> 16) & 0xF;
    
    descriptor->available = 0;
    
    descriptor->reserved = 0;
    
    descriptor->is32bit = 1;
    
    descriptor->granularity = 1;
    
    descriptor->baseH8 = (base >> 24) & 0xFF;
}

///
/// Initialize a 32-bit page-addressed data segment
///
/// @param descriptor The segment descriptor to be initialized
/// @param base The base address of the segment
/// @param limit The limit of the segment
/// @param privilegeLevel The privilege level of the segment
///
void SegmentDescriptorInitializeDataSegment(struct SegmentDescriptor* descriptor, UInt32 base, UInt32 limit, UInt32 privilegeLevel)
{
    descriptor->limitL16 = limit & 0xFFFF;
    
    descriptor->baseL16 = base & 0xFFFF;
    
    descriptor->baseM8 = (base >> 16) & 0xFF;
    
    descriptor->accessed = 0;
    
    descriptor->rwaccess = 1;
    
    descriptor->dcbit = 0;
    
    descriptor->isCode = 0;
    
    descriptor->isNonSystem = 1;
    
    descriptor->privilegeLevel = privilegeLevel;
    
    descriptor->isPresent = 1;
    
    descriptor->limitH4 = (limit >> 16) & 0xF;
    
    descriptor->available = 0;
    
    descriptor->reserved = 0;
    
    descriptor->is32bit = 1;
    
    descriptor->granularity = 1;
    
    descriptor->baseH8 = (base >> 24) & 0xFF;
}
