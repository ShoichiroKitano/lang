.globl add
.p2align 4, 0x90
add:
  pushq %rbp
  movq %rsp, %rbp
  movl $1, %eax
  addl $2, %eax
  pushq %rbp
  retq
