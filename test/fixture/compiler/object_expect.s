.globl _add1
.p2align 4, 0x90
_add1:
  pushq %rbp
  movq %rsp, %rbp
  subq $16, %rsp
  movl %edi, -4(%rbp)
  movl %esi, -8(%rbp)
  movl $1, %eax
  addl $2, %eax
  addq $16, %rsp
  popq %rbp
  retq
