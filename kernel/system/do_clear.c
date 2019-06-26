/* The kernel call implemented in this file:
 *   m_type:	SYS_CLEAR
 *
 * The parameters for this kernel call are:
 *    m1_i1:	PR_ENDPT		(endpoint of process to clean up)
 */

#include "kernel/system.h"

#include <minix/endpoint.h>
/** Added by EKA */
#include "../arch/i386/hproto.h"
#include "../arch/i386/htype.h"
/** End added by EKA */
#if USE_CLEAR

/*===========================================================================*
 *				do_clear				     *
 *===========================================================================*/
int do_clear(struct proc * caller, message * m_ptr)
{
/* Handle sys_clear. Only the PM can request other process slots to be cleared
 * when a process has exited.
 * The routine to clean up a process table slot cancels outstanding timers, 
 * possibly removes the process from the message queues, and resets certain 
 * process table fields to the default values.
 */
  struct proc *rc;
  int exit_p;
  int i;

  if(!isokendpt(m_ptr->PR_ENDPT, &exit_p)) { /* get exiting process */
      return EINVAL;
  }
  rc = proc_addr(exit_p);	/* clean up */

  release_address_space(rc);

  /* Don't clear if already cleared. */
  if(isemptyp(rc)) return OK;

  /* Check the table with IRQ hooks to see if hooks should be released. */
  for (i=0; i < NR_IRQ_HOOKS; i++) {
      if (rc->p_endpoint == irq_hooks[i].proc_nr_e) {
        rm_irq_handler(&irq_hooks[i]);	/* remove interrupt handler */
        irq_hooks[i].proc_nr_e = NONE;	/* mark hook as free */
      } 
  }

  /* Add by EKA: free the PE working set list */

   if(rc->p_hflags & PROC_TO_HARD){
#if 1
      printf("###STATS : %s %d ticks: %d user: %d sys: %d #####"
             "#PE %d #NMI %d #US1_US2_SIZE %d #abortpe %d #sspe %d"
             "#injected_fault %d #dwc_d %d #exception_d %d\n", 
         rc->p_name, rc->p_endpoint, rc->p_ticks, rc->p_user_time, 
         rc->p_sys_time, rc->p_nb_pe, rc->p_nb_nmi, rc->p_lus1_us2_size,
         rc->p_nb_abort, rc->p_nb_ss, rc->p_nb_inj_fault, rc->p_nb_dwc_d_f,
         rc->p_nb_exception_d_f);
      printf("## Cycles %s total %d %d chk_vaddr %d %d reset_pram %d %d "
         " set_to_ro %d %d cmp %d %d\n",
              rc->p_name, ex64hi(rc->p_cycles), ex64lo(rc->p_cycles), 
              ex64hi(rc->p_check_vaddr_2_tsc), ex64lo(rc->p_check_vaddr_2_tsc),
              ex64hi(rc->p_reset_pram_tsc), ex64lo(rc->p_reset_pram_tsc),
              ex64hi(rc->p_set_ro_tsc), ex64lo(rc->p_set_ro_tsc),
              ex64hi(rc->p_cmp_tsc), ex64lo(rc->p_cmp_tsc));
      printf("## Times %s total %d  chk_vaddr %d  reset_pram %d "
         " set_to_ro %d cmp %d\n",
              rc->p_name, cpu_time_2_ms(rc->p_cycles), rc->p_check_vaddr_2_t, 
              rc->p_reset_pram_t, rc->p_set_ro_t, rc->p_cmp_t);
#endif
      free_pram_mem_blocks(rc, 1);
      handle_hsr_events(rc);
      free_hsrs(rc);
      reset_hardening_attri(rc);
  }
  /**End Add by EKA**/

  /* Remove the process' ability to send and receive messages */
  clear_endpoint(rc);

  /* Turn off any alarm timers at the clock. */   
  reset_timer(&priv(rc)->s_alarm_timer);
  /* Make sure that the exiting process is no longer scheduled,
   * and mark slot as FREE. Also mark saved fpu contents as not significant.
   */
  RTS_SETFLAGS(rc, RTS_SLOT_FREE);
  
  /* release FPU */
  release_fpu(rc);
  rc->p_misc_flags &= ~MF_FPU_INITIALIZED;

  /* Release the process table slot. If this is a system process, also
   * release its privilege structure.  Further cleanup is not needed at
   * this point. All important fields are reinitialized when the 
   * slots are assigned to another, new process. 
   */
  if (priv(rc)->s_flags & SYS_PROC) priv(rc)->s_proc_nr = NONE;

#if 0
  /* Clean up virtual memory */
  if (rc->p_misc_flags & MF_VM) {
  	vm_map_default(rc);
  }
#endif

  return OK;
}

#endif /* USE_CLEAR */

