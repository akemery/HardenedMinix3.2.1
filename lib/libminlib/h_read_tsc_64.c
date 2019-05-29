#include <minix/u64.h>
#include <minix/minlib.h>

/* Utility function to work directly with u64_t
 * By Antonio Mancina
 */
/* Modifiy by EKA to make a system call*/
void h_read_tsc_64(t)
u64_t* t;
{
    u32_t lo, hi;
    h_read_tsc (&hi, &lo);
    *t = make64 (lo, hi);
}

