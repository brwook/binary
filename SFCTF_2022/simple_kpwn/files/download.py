#!/usr/bin/env python3
import string
import os
import sys
import mediafire_dl

def main():
    url = input("give me your binary link: ")

    rs = sys.argv[1]
    ROOTFS_NAME = '/chall/' + rs
    os.mkdir(ROOTFS_NAME)
    path = os.path.join(ROOTFS_NAME, "result")

    mediafire_dl.download(url, path, quiet=True)
    return 0

if __name__ == "__main__":
    main()
