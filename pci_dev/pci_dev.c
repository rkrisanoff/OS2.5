#include <linux/kernel.h>
#include "../lab_types.h"
#include <linux/syscalls.h>
#include <linux/pci.h>
#include <linux/vmalloc.h>
struct pci_dev *dev;
SYSCALL_DEFINE1(pci_dev,struct lab_pci_dev_data *, lpdd_user)
{

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

    return 0;
}
