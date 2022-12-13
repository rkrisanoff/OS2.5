#include <linux/kernel.h>
#include "../lab_types.h"
#include <linux/syscalls.h>
#include <linux/pid.h>
#include <linux/sched/signal.h>
#include <linux/vmalloc.h>

SYSCALL_DEFINE2(cpu_itimer, pid_t, pid_user, struct lab_cpu_itimer_data *, lcid_user)
{
	struct task_struct *task = NULL;
	struct pid *pid_struct = find_get_pid(pid_user);
	if (pid_struct == NULL)
	{
		printk(KERN_INFO "PID %d doesn't exist", pid_user);
		return 1;
	}
	task = pid_task(pid_struct, PIDTYPE_PID);
	printk(KERN_INFO "I'm here %d\n", pid_user);
	task = get_pid_task(find_get_pid(pid_user), PIDTYPE_PID);

	if (task == NULL)
	{
		printk(KERN_INFO "Process with PID=%d doesn't exist", pid_user);
		return 2;
	}
	struct lab_cpu_itimer_data *lcid = vmalloc(sizeof(struct lab_cpu_itimer_data));
	struct cpu_itimer it_ITIMER_PROF = task->signal->it[0];
	struct cpu_itimer it_ITIMER_VIRTUAL = task->signal->it[1];

	lcid->it_ITIMER_PROF.expires = it_ITIMER_PROF.expires;
	lcid->it_ITIMER_PROF.incr = it_ITIMER_PROF.incr;
	lcid->it_ITIMER_VIRTUAL.expires = it_ITIMER_VIRTUAL.expires;
	lcid->it_ITIMER_VIRTUAL.incr = it_ITIMER_VIRTUAL.incr;
	copy_to_user(lcid_user, lcid, sizeof(struct lab_cpu_itimer_data));
	vfree(lcid);
	return 0;
};
