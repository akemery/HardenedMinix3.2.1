#include <stdio.h>
#include <stdint.h>
#include <x86intrin.h>
#include <minix/type.h>
#include <machine/vm.h>

#include "kernel/kernel.h"
#include "kernel/vm.h"

u32_t compute_crc32 (u32_t *data_addr)
    {
    int index;
    u32_t crc32 = 0;
    for (index = 0; index < I386_PAGE_SIZE / sizeof(u32_t); index++)
        crc32 = _mm_crc32_u32 (crc32, *data_addr++); 
    return(crc32);
}


