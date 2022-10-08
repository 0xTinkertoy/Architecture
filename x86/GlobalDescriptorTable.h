//
//  GlobalDescriptorTable.h
//  Kernel-x86
//
//  Created by FireWolf on 8/15/20.
//  Copyright © 2020 FireWolf. All rights reserved.
//

#ifndef GlobalDescriptorTable_h
#define GlobalDescriptorTable_h

#ifdef __cplusplus
extern "C" {
#endif

/// Initialize the Global Descriptor Table
void GDTInitialize(void);

#ifdef __cplusplus
}
#endif

#endif /* GlobalDescriptorTable_h */
