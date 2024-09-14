QEMU_PATH=qemu-system-x86_64

FS_IMAGE_PATH=xubuntu_caos_2021.qcow2

CPU_COUNT=4
MEMORY_MB=4096

${QEMU_PATH} \
        -smp ${CPU_COUNT} \
        -m ${MEMORY_MB} \
        -name xubuntu_caos_2021 \
        -hda ${FS_IMAGE_PATH} \
        -vga virtio \
        -display default,show-cursor=on \
        -usb \
        -accel tcg \
        -chardev qemu-vdagent,id=ch1,name=vdagent,clipboard=on \
        -device virtio-serial-pci \
        -device virtserialport,chardev=ch1,id=ch1,name=com.redhat.spice.0

