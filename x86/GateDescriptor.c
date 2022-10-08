//
//  GateDescriptor.c
//  Kernel-x86
//
//  Created by FireWolf on 8/15/20.
//  Copyright © 2020 FireWolf. All rights reserved.
//

#include "GateDescriptor.h"

// MARK: Gate Type

/// 32-bit Interrupt Gate
#define kGateTypeIntr32 14

/// 32-bit Trap Gate
#define kGateTypeTrap32 15

/// 32-bit Task Gate
#define kGateTypeTask32 5

///
/// Initialize an interrupt gate descriptor
///
/// @param descriptor The gate descriptor to be initialized
/// @param selector Selector of the code segment of the handler
/// @param address Address of the handler
/// @param privilegeLevel Descriptor privilege level
///
void GateDescriptorInitializeInterruptGate(struct GateDescriptor* descriptor, UInt32 selector, UInt32 address, UInt32 privilegeLevel)
{
    descriptor->addressL16 = address & 0xFFFF;
    
    descriptor->codeSegmentSelector = selector;
    
    descriptor->reserved = 0;
    
    descriptor->type = kGateTypeIntr32;
    
    descriptor->privilegeLevel = privilegeLevel;
    
    descriptor->isPresent = 1;
    
    descriptor->addressH16 = (address >> 16) & 0xFFFF;
}

///
/// Initialize a trap gate descriptor
///
/// @param descriptor The gate descriptor to be initialized
/// @param selector Selector of the code segment of the handler
/// @param address Address of the handler
/// @param privilegeLevel Descriptor privilege level
///
void GateDescriptorInitializeTrapGate(struct GateDescriptor* descriptor, UInt32 selector, UInt32 address, UInt32 privilegeLevel)
{
    descriptor->addressL16 = address & 0xFFFF;
    
    descriptor->codeSegmentSelector = selector;
    
    descriptor->reserved = 0;
    
    descriptor->type = kGateTypeTrap32;
    
    descriptor->privilegeLevel = privilegeLevel;
    
    descriptor->isPresent = 1;
    
    descriptor->addressH16 = (address >> 16) & 0xFFFF;
}
