cmd_/home/minh/lab_driver/lab8/lab.ko := ld -r -m elf_x86_64  -z max-page-size=0x200000 -z noexecstack   --build-id  -T ./scripts/module-common.lds -o /home/minh/lab_driver/lab8/lab.ko /home/minh/lab_driver/lab8/lab.o /home/minh/lab_driver/lab8/lab.mod.o;  true
