#include <linux/usbdevice_fs.h>
#include <linux/usb/ch9.h>
#include <asm/byteorder.h>

#include <string.h>
#include <errno.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include <dirent.h>
#include <sys/ioctl.h>
#include <sys/types.h>

struct usb_handle
{
	char fname[64];
	int desc;
	unsigned char ep_in;
	unsigned char ep_out;
};

static inline int badname(const char *name)
{
    while(*name) {
        if(!isdigit(*name++)) return 1;
    }
    return 0;
}

static int is_fastboot(int fd) {
	struct usb_device_descriptor *dev;
	struct usb_interface_descriptor *ifc;
	char desc[1024];
	int n;

	n = read(fd, desc, sizeof(desc));
	dev = (void *)desc;
	fprintf(stderr, "found vid: %4x\n", dev->idVendor);
	fprintf(stderr, "found pid: %4x\n", dev->idProduct);
	if (dev->idVendor != 0x0bb4) return 0;
	if (dev->idProduct != 0x0fff) return 0;
};

int usb_write(struct usb_handle *h, const void *_data, int len) {
    unsigned char *data = (unsigned char*) _data;
    unsigned count = 0;
    struct usbdevfs_bulktransfer bulk;
    int n;

    if(h->ep_out == 0) {
        return -1;
    }

    if(len == 0) {
        bulk.ep = h->ep_out;
        bulk.len = 0;
        bulk.data = data;
        bulk.timeout = 0;

        n = ioctl(h->desc, USBDEVFS_BULK, &bulk);
        if(n != 0) {
            fprintf(stderr,"ERROR: n = %d, errno = %d (%s)\n",
                    n, errno, strerror(errno));
            return -1;
        }
        return 0;
    }

    while(len > 0) {
        int xfer;
        xfer = (len > 4096) ? 4096 : len;

        bulk.ep = h->ep_out;
        bulk.len = xfer;
        bulk.data = data;
        bulk.timeout = 0;

        n = ioctl(h->desc, USBDEVFS_BULK, &bulk);
        if(n != xfer) {
            fprintf(stderr, "ERROR: n = %d, errno = %d (%s)\n",
                n, errno, strerror(errno));
            return -1;
        }

        count += xfer;
        len -= xfer;
        data += xfer;
    }

    return count;
}

struct usb_handle *get_fastboot() {
	char busname[64], devname[64];
	DIR *busdir, *devdir;
	struct dirent *de;

	int fd;
	int found_usb = 0;
    int n;
    int ifc;

    struct usb_handle *usb;

	busdir = opendir("/dev/bus/usb");
    fprintf(stderr, "busdir: %p\n", busdir);

    while((de = readdir(busdir)) && (found_usb == 0)) {
        fprintf(stderr, "dirent: %p\n", de);
	    if(badname(de->d_name)) continue;
	    sprintf(busname, "%s/%s", "/dev/bus/usb", de->d_name);
	    fprintf(stderr, "busname: %s\n", busname);

        devdir = opendir(busname);

	    while((de = readdir(devdir)) && (found_usb == 0)) {
		    if(badname(de->d_name)) continue;
		    sprintf(devname, "%s/%s", busname, de->d_name);
		    fprintf(stderr, "devname: %s\n", devname);

		    if ((fd = open(devname, O_RDWR)) < 1) {
			    fprintf(stderr, "cannot open %s for writing\n", devname);
			    continue;	
		    };

		    if (is_fastboot(fd)) {
			    fprintf(stderr, "found fastboot.\n");

			    usb = calloc(1, sizeof(struct usb_handle));

			    usb->ep_in = 0x81;
			    usb->ep_out = 0x01;
			    usb->desc = fd;

                ifc = 1;
                n = ioctl(fd, USBDEVFS_CLAIMINTERFACE, &ifc);                
		    };
	    };
        closedir(devdir);
    };
    closedir(busdir);
    return usb;
};

int main() {
    struct usb_handle *usb;

    usb = get_fastboot();

    char *test1 = "reboot-bootloader";
    usb_write(usb, test1, strlen(test1));

};




