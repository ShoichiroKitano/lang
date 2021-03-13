.globl _add
.p2align 4, 0x90
_add:
  pushq %rbp
  movq %rsp, %rbp
  movl $1, %eax
  addl $2, %eax
  popq %rbp
  retq
