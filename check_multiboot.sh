#!/bin/bash
if grub-file --is-x86-multiboot2 $1 ;then
	echo "File $1 is multiboot2"
else
	echo "File $1 is NOT multiboot2"
fi
