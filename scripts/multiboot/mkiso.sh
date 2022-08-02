#!/bin/bash

#Check for multiboot of file
if grub-file --is-x86-multiboot $1 ;then
	echo "File $1 is multiboot"
else
	echo "File $1 is NOT multiboot"
	exit -1
fi

mkdir -pv iso/boot/grub
cp -v $1 iso/boot/monnos.bin
cp -v $(dirname "$0")/grub.cfg iso/boot/grub/grub.cfg
grub-mkrescue -o MONNOS.iso iso/
