#!/bin/bash

cd /chall
if [ ! -d tmp ] ; then
	mkdir tmp;
fi

ROOTFS_NAME="$(mktemp -u XXXXXXXXXX)"
/chall/download.py $ROOTFS_NAME
if [ $? -ne 0 ] ; then
        exit;
fi


chmod 755 $ROOTFS_NAME/result
cd $ROOTFS_NAME; cpio -id -v < /chall/rootfs.cpio 2>/dev/null;
cd ..

if [ $? -ne 0 ] ; then
	rm -dR $ROOTFS_NAME
	exit;
fi
cd $ROOTFS_NAME
find . | cpio -o --format=newc > /chall/tmp/$ROOTFS_NAME.cpio 2>/dev/null;
cd ..
rm -dR $ROOTFS_NAME

qemu-system-x86_64 \
-m 128M \
-kernel ./bzImage \
-initrd /chall/tmp/$ROOTFS_NAME.cpio \
-append "root=/dev/ram rw console=ttyS0 oops=panic panic=1 quiet kaslr" \
-netdev user,id=t0, -device e1000,netdev=t0,id=nic0 \
-nographic \
-cpu qemu64 \
-no-reboot

rm /chall/tmp/$ROOTFS_NAME.cpio

