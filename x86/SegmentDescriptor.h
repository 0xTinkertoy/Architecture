//
//  SegmentDescriptor.h
//  Kernel-x86
//
//  Created by FireWolf on 8/15/20.
//  Copyright © 2020 FireWolf. All rights reserved.
//

#ifndef SegmentDescriptor_h
#define SegmentDescriptor_h

#include <Types.hpp>

/// Represents an entry in the Global Descriptor Table
struct SegmentDescriptor
{
    /// Low 16 bits of the segment limit
    UInt16 limitL16;
    
    /// Low 16 bits of the segment base address
    UInt16 baseL16;
    
    /// Middle 8 bits of the segment base address
    UInt8 baseM8;
    
    /// CPU sets to 1 when the segment is accessed
    UInt8 accessed: 1;
    
    /// Readable bit for CS: Sets to 1 if reading from CS is allowed;
    /// Writable bit for DS: Sets to 1 if writing to DS is allowed.
    UInt8 rwaccess: 1;
    
    /// Conforming bit for CS:
    ///     Sets to 1 if code can be executed from an equal or lower privilege level;
    ///     Sets to 0 if the code can only be executed from defined privilege level
    /// Direction bit for DS:
    ///     Sets to 1 if the segment grows down; 0 if the segment grows up.
    UInt8 dcbit: 1;
    
    /// Indicate whether this is a code segment
    UInt8 isCode: 1;
    
    /// Indicate whether this is not a system segment, e.g. a Task State Segment
    ///     Sets to 1 for code or data segments; 0 for system segments
    UInt8 isNonSystem: 1;
    
    /// Descriptor Privilege level (DPL): Ring 0 for the kernel; Ring 3 for user applications
    UInt8 privilegeLevel: 2;
    
    /// Indicate whether this segment presents
    UInt8 isPresent: 1;
    
    /// High 4 bits of the segment limit
    UInt8 limitH4: 4;
    
    /// Unused 1 bit available for the system
    UInt8 available: 1;
    
    /// Reserved 1 bit initialized to 0
    UInt8 reserved: 1;
    
    /// Indicate whether this is a 32-bit segment
    UInt8 is32bit: 1;
    
    /// The granularity of memory unit: 1 if 4 KB; 0 if 1 byte
    UInt8 granularity: 1;
    
    /// High 8 bits of the segment base address
    UInt8 baseH8;
};

///
/// Initialize a 32-bit page-addressed code segment
///
/// @param descriptor The segment descriptor to be initialized
/// @param base The base address of the segment
/// @param limit The limit of the segment
/// @param privilegeLevel The privilege level of the segment
///
void SegmentDescriptorInitializeCodeSegment(struct SegmentDescriptor* descriptor, UInt32 base, UInt32 limit, UInt32 privilegeLevel);

///
/// Initialize a 32-bit page-addressed data segment
///
/// @param descriptor The segment descriptor to be initialized
/// @param base The base address of the segment
/// @param limit The limit of the segment
/// @param privilegeLevel The privilege level of the segment
///
void SegmentDescriptorInitializeDataSegment(struct SegmentDescriptor* descriptor, UInt32 base, UInt32 limit, UInt32 privilegeLevel);

#endif /* SegmentDescriptor_h */
