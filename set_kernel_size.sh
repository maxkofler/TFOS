#!/usr/bin/bash

kernel_blocks=$(du -s -B 512 kernel.bin | grep -o '^[0-9]\+')
kernel_blocks=$(echo $kernel_blocks + 1 | bc)

echo "Kernel size:" $kernel_blocks "blocks of 512b"
echo "KERNEL_LEN equ" $kernel_blocks > bootloader/kernel_len.asm