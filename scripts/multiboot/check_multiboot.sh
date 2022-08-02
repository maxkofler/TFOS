#!/bin/bash
if grub-file --is-x86-multiboot $1 ;then
	echo "File $1 is multiboot"
else
	echo "File $1 is NOT multiboot"
fi
