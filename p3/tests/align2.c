/* a few allocations in multiples of 4 bytes checked for alignment */
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include "mem.h"

int main() {
    assert(Init_Mem(4096) == 0);
    int* ptr[4];

    ptr[0] = (int*) Alloc_Mem(4);
    ptr[1] = (int*) Alloc_Mem(8);
    ptr[2] = (int*) Alloc_Mem(16);
    ptr[3] = (int*) Alloc_Mem(24);

    for (int i = 0; i < 4; i++) {
        assert(((int)ptr[i]) % 8 == 0);
    }

    exit(0);
}
