if grub-file --is-x86-multiboot build/tfos.bin; then
  echo file is multiboot
else
  echo the file is not multiboot
fi
