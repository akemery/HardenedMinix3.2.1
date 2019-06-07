#include "kernel/system.h"
#include "kernel/arch/i386/include/arch_proto.h"
#include "kernel/arch/i386/hproto.h"
#include "kernel/arch/i386/htype.h"
#include <assert.h>



/*===========================================================================*
 *			          do_hsr				     *
 *===========================================================================*/
int do_hsr(struct proc * caller, message * m_ptr)
{
  proc_nr_t proc_nr, proc_nr_e;
  struct proc *p;

  proc_nr_e= (proc_nr_t) m_ptr->HSR_ENDPT;

  if (!isokendpt(proc_nr_e, &proc_nr)) return(EINVAL);
  
  p = proc_addr(proc_nr);
  
  if(p->p_hflags & PROC_TO_HARD){
     printf("Got shared region att %d 0x%lx 0x%lx %d\n", p->p_nr,
     m_ptr->HSR_VADDR, m_ptr->HSR_LENGTH, m_ptr->HSR_R_ID);
       add_hsr(p, m_ptr->HSR_VADDR,
           m_ptr->HSR_LENGTH,m_ptr->HSR_R_ID);
       p->p_hflags |= PROC_SHARING_MEM;
  }
  return(OK);
}
