#include "syslib.h"

int sys_hsr(proc_endpt, hsr_vaddr, 
	hsr_length, r_id)
endpoint_t proc_endpt;		/* process endpoint */
vir_bytes hsr_vaddr;		/* HSR Vaddr */
vir_bytes hsr_length;		/* HSR length */
int r_id;                       /* HSR id*/
{
/* Send to the kernel from the VM the phys addr of allocated frame
 */

  message m;

  m.HSR_ENDPT        = proc_endpt;
  m.HSR_VADDR        = (long) hsr_vaddr;
  m.HSR_LENGTH       = (long) hsr_length;
  m.HSR_R_ID             = r_id;

  return(_kernel_call(SYS_HSR, &m));
}
