cmd_/home/minh/lab_driver/lab3/bai2/bai2.ko := ld -r -m elf_x86_64  -z max-page-size=0x200000 -z noexecstack   --build-id  -T ./scripts/module-common.lds -o /home/minh/lab_driver/lab3/bai2/bai2.ko /home/minh/lab_driver/lab3/bai2/bai2.o /home/minh/lab_driver/lab3/bai2/bai2.mod.o;  true
