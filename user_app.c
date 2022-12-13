#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include "lab_types.h"

#define __NR_syscall_cpu_itimer 450
#define __NR_syscall_pci_dev 449
int main(int argc, char **argv)
{
    int fd;

    if (argc < 2 || (strcmp(argv[1], "help") == 0))
    {
        printf("Usage %s <PID> <PAGE-NUMBER>\n", argv[0]);
        printf("<PID> must be integer more than zero\n");

        return 0;
    }
    int pid = atoi(argv[1]);
    if (pid)
    {
        printf("Entered <PID> is %d\n", pid);
    }
    else
    {
        printf("Wrong <PID>\n");
        return 1;
    }

    struct lab_cpu_itimer_data * lcid = malloc(sizeof (struct lab_cpu_itimer_data));
    int ret_val = syscall(__NR_syscall_cpu_itimer, pid, lcid);
    if (ret_val != 0)
    {
        printf("__NR_syscall_cpu_itimer failed %d: process with <PID> = doesn't exist\n", ret_val);
        exit(ret_val);
    }
    printf("<-- syscall_cpu_timer -->\n");
    printf("For ITIMER_PROF Expires: [%llu], Incr: [%llu]\n",
           lcid->it_ITIMER_PROF.expires, lcid->it_ITIMER_PROF.incr);

    printf("For ITIMER_VIRTUAL Expires: [%llu], Incr: [%llu]\n",
           lcid->it_ITIMER_VIRTUAL.expires, lcid->it_ITIMER_VIRTUAL.incr);

    struct lab_pci_dev_data * lpdd = malloc(sizeof (struct lab_pci_dev_data));
    ret_val = syscall(__NR_syscall_pci_dev, 10, lpdd);
    if (ret_val != 0)
    {
        printf("syscall_pci_dev failed %d: process with <PID> = %d doesn't exist\n", ret_val);
        exit(ret_val);
    }
    printf("<-- syscall_pci_dev -->\n");
    if (lpdd->find_device){
        printf("pci found [%d]\n", lpdd->device);
    } else {
        printf("There are not any deviced\n");
    }

    return 0;
}
