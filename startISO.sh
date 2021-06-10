if grub-file --is-x86-multiboot build/tfos.bin; then
    echo file is multiboot

    mkdir -p iso/boot/grub

    cp build/tfos.bin iso/boot/tfos.bin

    cp grub.cfg iso/boot/grub/grub.cfg

    grub-mkrescue -o tfos.iso iso

    qemu-system-x86_64 -cpu pentium2 -cdrom tfos.iso

else
    echo the file is not multiboot
fi