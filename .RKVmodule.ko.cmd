cmd_/root/oslab/ex4/RKVmodule.ko := ld -r -m elf_x86_64  -z max-page-size=0x200000 -T /usr/src/linux-headers-4.19.0-13-common/scripts/module-common.lds  --build-id  -o /root/oslab/ex4/RKVmodule.ko /root/oslab/ex4/RKVmodule.o /root/oslab/ex4/RKVmodule.mod.o ;  true
