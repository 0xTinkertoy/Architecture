//
//  InterruptVectorTable.cpp
//  Kernel-ARM~Moisture
//
//  Created by FireWolf on 2/24/21.
//

#include "InterruptVectorTable.hpp"
#include <Debug.hpp>

#define OSDefineDefaultISR(name) \
void name()                      \
{                                \
    PANIC("Unhandled Exception @ ISR = %d.", *reinterpret_cast<UInt32*>(0xE000ED04) & 0xFF); \
}

OSDefineDefaultISR(DefaultISR)
#define NMIHandler          DefaultISR
#define HardFaultHandler    DefaultISR
#define MemManageHandler    DefaultISR
#define BusFaultHandler     DefaultISR
#define UsageFaultHandler   DefaultISR
#define SVCHandler          DefaultISR
#define DebugMonHandler     DefaultISR
#define PendSVHandler       DefaultISR
#define SysTickHandler      DefaultISR

/// The kernel interrupt vector table
volatile InterruptVectorTable::Handler InterruptVectorTable::table[kNumEntries] __attribute__((aligned (128)));

/// Setup the interrupt vector table
void InterruptVectorTable::setup()
{
    InterruptVectorTable::registerHandler(2, NMIHandler);
    InterruptVectorTable::registerHandler(3, HardFaultHandler);
    InterruptVectorTable::registerHandler(4, MemManageHandler);
    InterruptVectorTable::registerHandler(5, BusFaultHandler);
    InterruptVectorTable::registerHandler(6, UsageFaultHandler);
    InterruptVectorTable::registerHandler(11, SVCHandler);
    InterruptVectorTable::registerHandler(12, DebugMonHandler);
    InterruptVectorTable::registerHandler(14, PendSVHandler);
    InterruptVectorTable::registerHandler(15, SysTickHandler);

    // Relocate the interrupt vector table
    static constexpr UInt32 VTOR = 0xE000ED08;
    *reinterpret_cast<volatile UInt32*>(VTOR) = reinterpret_cast<UInt32>(InterruptVectorTable::table);
    asm("dsb");

    pinfo("Kernel interrupt vector table is initialized at 0x%p.", InterruptVectorTable::table);
}

/// Register the interrupt handler
void InterruptVectorTable::registerHandler(UInt32 exception, Handler handler)
{
    passert(exception < InterruptVectorTable::kNumEntries, "The given IRQ number %d is invalid.", exception);

    table[exception] = handler;
}

/// Unregister the interrupt handler
void InterruptVectorTable::unregisterHandler(UInt32 exception)
{
    return InterruptVectorTable::registerHandler(exception, DefaultISR);
}