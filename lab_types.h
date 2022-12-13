#ifndef LAB_TYPES_H
#define LAB_TYPES_H


struct lab_cpu_itimer
{
    unsigned long long expires;
    unsigned long long incr;
};

struct lab_cpu_itimer_data
{
    struct lab_cpu_itimer it_ITIMER_PROF;
    struct lab_cpu_itimer it_ITIMER_VIRTUAL;
};
struct lab_pci_dev_data
{
    int find_device;
    unsigned short device;
};

#endif