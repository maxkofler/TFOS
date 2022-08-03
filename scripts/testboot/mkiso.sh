#!/bin/bash

mkdir -pv iso/boot/grub
cp -v $1 iso/boot/monnos.bin
cp -v $(dirname "$0")/grub.cfg iso/boot/grub/grub.cfg
grub-mkrescue -o MONNOS.iso iso/
