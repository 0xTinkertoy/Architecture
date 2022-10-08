//
//  i386.h
//  Kernel-x86
//
//  Created by FireWolf on 8/14/20.
//  Copyright © 2020 FireWolf. All rights reserved.
//

#ifndef i386_h
#define i386_h

// MARK: Index of each segment in the GDT
#define kKernCodeSegment 1
#define kKernDataSegment 2
#define kUserCodeSegment 3
#define kUserDataSegment 4

// MARK: Processor Privilege Level
#define kKernPrivilegeLevel 0
#define kUserPrivilegeLevel 3

static inline unsigned short getCS()
{
    unsigned short cs;

    asm volatile("movw %%cs, %%ax \n"
                 "movw %%ax, %[cs]\n"
    : [cs] "=g" (cs)
    :
    :
    );

    return cs;
}

#endif /* i386_h */
