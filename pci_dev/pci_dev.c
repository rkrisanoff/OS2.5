#include <linux/kernel.h>
#include "../lab_types.h"
#include <linux/syscalls.h>
#include <linux/pci.h>
#include <linux/vmalloc.h>

pthread_mutex_t mutex;

struct pci_dev *dev;

SYSCALL_DEFINE1(pci_dev, struct lab_pci_dev_data *, lpdd_user)
{
    pthread_mutex_init(&mutex, NULL);
    pthread_mutex_lock(&mutex);

    struct lab_pci_dev_data *lpdd = vmalloc(sizeof(struct lab_pci_dev_data));
    lpdd->find_device = 0;
    struct pci_dev *dev = pci_get_device(PCI_ANY_ID, PCI_ANY_ID, NULL);
    if (dev != NULL)
    {
        lpdd->device = dev->device;
        lpdd->find_device = 1;
    };
    copy_to_user(lpdd_user, lpdd, sizeof(struct lab_pci_dev_data));
    vfree(lpdd);

    pthread_mutex_unlock(&mutex);
    pthread_mutex_destroy(&mutex);
    return 0;
}
