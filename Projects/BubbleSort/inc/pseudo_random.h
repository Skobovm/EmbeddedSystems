//
// Pseudo-Random Number Generator
//

#include <stdio.h>
#include "nucleoboard.h"

// Re-init with a given seed
void Initialize(const uint32_t  seed);

// Obtain a 32-bit random number
uint32_t ExtractU32();