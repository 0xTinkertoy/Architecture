//
//  GateDescriptor.h
//  Kernel-x86
//
//  Created by FireWolf on 8/15/20.
//  Copyright © 2020 FireWolf. All rights reserved.
//

#ifndef GateDescriptor_h
#define GateDescriptor_h

#include <Types.hpp>

/// Represents an entry in the Interrupt Descriptor Table
struct GateDescriptor
{
    /// Low 16 bits of the address of the interrupt handler
    UInt16 addressL16;
    
    /// Selector of the code segment of the interrupt handler
    UInt16 codeSegmentSelector;
    
    /// Reserved and unused byte
    UInt8 reserved;
    
    /// Gate type
    UInt8 type: 5;
    
    /// Descriptor privilege level (DPL)
    UInt8 privilegeLevel: 2;

    /// Indicate whether this entry presents
    UInt8 isPresent: 1;
    
    /// High 16 bits of the address of the interrupt handler
    UInt16 addressH16;
};

///
/// Initialize an interrupt gate descriptor
///
/// @param descriptor The gate descriptor to be initialized
/// @param selector Selector of the code segment of the handler
/// @param address Address of the handler
/// @param privilegeLevel Descriptor privilege level
///
void GateDescriptorInitializeInterruptGate(struct GateDescriptor* descriptor, UInt32 selector, UInt32 address, UInt32 privilegeLevel);

///
/// Initialize a trap gate descriptor
///
/// @param descriptor The gate descriptor to be initialized
/// @param selector Selector of the code segment of the handler
/// @param address Address of the handler
/// @param privilegeLevel Descriptor privilege level
///
void GateDescriptorInitializeTrapGate(struct GateDescriptor* descriptor, UInt32 selector, UInt32 address, UInt32 privilegeLevel);

#endif /* GateDescriptor_h */
