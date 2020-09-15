push %r12
mov $0x3539623939376661,%r12
mov %r12, 0xff0(%rsp)
lea 0xff0(%rsp),%rdi
pop %r12
retq
