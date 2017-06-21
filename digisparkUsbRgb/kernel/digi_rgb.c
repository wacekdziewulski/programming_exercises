/* Derived from: https://github.com/mavam/ml-driver/blob/master/ml_driver.c */

#include <linux/module.h>
#include <linux/init.h>

#include <linux/slab.h>         /* kmalloc() */
#include <linux/usb.h>          /* usb related stuff */
#include <linux/mutex.h>        /* mutexes */

#define DIGISPARK_VENDOR_ID  0x16c0
#define DIGISPARK_PRODUCT_ID 0x05df
#define DIGISPARK_ALT_VENDOR_ID  0x16d0
#define DIGISPARK_ALT_PRODUCT_ID 0x0753
#define DIGISPARK_MODULE_LOG_PREFIX "DigisparkRGB"
#define DIGISPARK_MINOR_BASE 0
#define DIGISPARK_RGB_DEV_NAME "digispark_rgb"

static struct usb_device_id digispark_table [] = {
    { USB_DEVICE(DIGISPARK_VENDOR_ID, DIGISPARK_PRODUCT_ID) },
    { USB_DEVICE(DIGISPARK_ALT_VENDOR_ID, DIGISPARK_ALT_PRODUCT_ID) }
};

MODULE_DEVICE_TABLE (usb, digispark_table);

static DEFINE_MUTEX(disconnect_mutex);

struct digispark_rgb_module {
    struct usb_device*      udev;
    struct usb_interface*   interface;
    unsigned char           minor;
    int                     open_count; /* Open count for this port */
    struct semaphore        sem;        /* Locks this structure */
};

static void digispark_log(const char* const message) {
    printk("%s: %s\n", DIGISPARK_MODULE_LOG_PREFIX, message);
}

static int digispark_rgb_open(struct inode *inode, struct file *file)
{
    /* open syscall */
    return 0;
}

static int digispark_rgb_release(struct inode *inode, struct file *file)
{
    /* close syscall */
    return 0;
}

static ssize_t digispark_rgb_write(struct file *file, const char __user *user_buf, size_t count, loff_t *ppos)
{
    /* write syscall */
    return 0;
}

static struct file_operations digispark_rgb_fops = {
    .owner =    THIS_MODULE,
    .write =    digispark_rgb_write,
    .open =     digispark_rgb_open,
    .release =  digispark_rgb_release,
};

static struct usb_class_driver digispark_rgb_class = {
    .name = DIGISPARK_RGB_DEV_NAME"%d",
    .fops = &digispark_rgb_fops,
    .minor_base = DIGISPARK_MINOR_BASE,
};

static inline void digispark_delete(struct digispark_rgb_module *dev)
{
    kfree(dev);
}

static int digispark_probe(struct usb_interface* interface, const struct usb_device_id* id)
{
    int retval;
    char msg[128];

    struct usb_device *udev = interface_to_usbdev(interface);
    struct digispark_rgb_module *dev = NULL;
    
    digispark_log("Probing device...");

    if (! udev) {
        digispark_log("udev is NULL, cannot initialize driver");
        goto exit;
    }

    dev = kzalloc(sizeof(struct digispark_rgb_module), GFP_KERNEL);
    if (! dev) {
        digispark_log("cannot allocate memory for struct digispark_rgb_module");
        retval = -ENOMEM;
        goto exit;
    }

    /* Save our data pointer in this interface device. */
    usb_set_intfdata(interface, dev);

    /* We can register the device now, as it is ready. */
    retval = usb_register_dev(interface, &digispark_rgb_class);
    if (retval) {
        digispark_log("not able to get a minor for this device.");
        usb_set_intfdata(interface, NULL);
        goto error;
    }

    sema_init(&dev->sem, 1);

    dev->minor = interface->minor;

    sprintf(msg, "Attached to /dev/%s%d", DIGISPARK_RGB_DEV_NAME, interface->minor - DIGISPARK_MINOR_BASE);
    digispark_log(msg);

    exit:
        return retval;

    error:
        digispark_delete(dev);

    return retval;
}

static void digispark_disconnect(struct usb_interface *interface)
{
    struct digispark_rgb_module *dev;
    int minor;
    char msg[128];

    mutex_lock(&disconnect_mutex);  /* Not interruptible */

    dev = usb_get_intfdata(interface);
    usb_set_intfdata(interface, NULL);

    down(&dev->sem); /* Not interruptible */

    minor = dev->minor;

    /* Give back our minor. */
    usb_deregister_dev(interface, &digispark_rgb_class);

    /* If the device is not opened, then we clean up right now. */
    if (! dev->open_count) {
        up(&dev->sem);
        digispark_delete(dev);
    } else {
        dev->udev = NULL;
        up(&dev->sem);
    }

    mutex_unlock(&disconnect_mutex);
    
    sprintf(msg, "/dev/%s%d now disconnected.", DIGISPARK_RGB_DEV_NAME, minor - DIGISPARK_MINOR_BASE);
    digispark_log(msg);
}

static struct usb_driver digispark_rgb_driver = {
    .name = "Digispark RGB LED",
    .id_table = digispark_table,
    .probe = digispark_probe,
    .disconnect = digispark_disconnect,
};

static int __init digispark_rgb_module_init(void)
{
    int result = usb_register(&digispark_rgb_driver);

    digispark_log("Module driver loaded");
    
    if (result) {
        digispark_log("Registering driver failed!");
    } else {
        digispark_log("Registered successfully");
    }

    return 0;
}

static void __exit digispark_rgb_module_exit(void)
{
    digispark_log("Removing module driver");
    usb_deregister(&digispark_rgb_driver);
}

module_init(digispark_rgb_module_init);
module_exit(digispark_rgb_module_exit);

MODULE_AUTHOR("Waclaw Dziewulski");
MODULE_LICENSE("GPL");
