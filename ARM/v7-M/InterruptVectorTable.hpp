//
//  InterruptVectorTable.hpp
//  Kernel-ARM~Moisture
//
//  Created by FireWolf on 2/24/21.
//

#ifndef InterruptVectorTable_hpp
#define InterruptVectorTable_hpp

#include <Types.hpp>

struct InterruptVectorTable
{
public:
    /// The interrupt handler type
    using Handler = void (*)();

    /// Setup the interrupt vector table
    static void setup();

    /// Register the interrupt handler
    static void registerHandler(UInt32 exception, Handler handler);

    /// Unregister the interrupt handler
    static void unregisterHandler(UInt32 exception);

    /// Get the address of the handler in assembly
    static inline Handler AssemblyHandler(Handler handler)
    {
        // The label declared in the inline assembly block must set the lowest bit to 1
        // Otherwise the T bit is cleared when the processor jumps to the entry point, resulting a usage fault (INVSTATE).
        return reinterpret_cast<Handler>(reinterpret_cast<UInt32>(handler) | 0x01);
    }

private:
    /// The number of entries in the vector table
    static constexpr size_t kNumEntries = 24; /* Include UART Interrupts */

    /// The kernel interrupt vector table
    static volatile Handler table[kNumEntries] __attribute__((aligned(128), section(".kernel.isr_table")));
};

#endif /* InterruptVectorTable_hpp */
