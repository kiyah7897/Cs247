# Writes Allow the user to enter a sequence of up to 10 numbers or until '0' is entered, 
# print back the numbers that have any of bits 3, 5 or 6 set (bit mask 00110100) Runs on 64-bit Linux only.
# To assemble and run:
#
#     gcc -no-pie -z noexecstack mask.s -o mask
# ----------------------------------------------------------------------------------------

          .global    main

          .text
main:     mov       $0, %r15
    input_loop:
          cmp       $10, %r15
          je        done

          mov       $1, %rax
          mov       $1, %rdi
          mov       $prompt, %rsi
          mov       $24, %rdx
          syscall

          mov       $0, %rax
          mov       $0, %rdi
          mov       $buf, %rsi
          mov       $100, %rdx
          syscall

          mov       $buf, %rdi
          call      atoi
          mov       %rax, %r12

          cmp       $0, %r12
          je        done

          mov       %r12d, nums(,%r15,4)
          inc       %r15
          jmp       input_loop
    done:
          mov       $0, %r14

    mask_loop:
          cmp       %r15, %r14
          je        exit

          mov       nums(,%r14,4), %r13d
          and       $0x34, %r13d
          cmp       $0, %r13d
          je        skip

          mov       $printnums, %rdi
          mov       nums(,%r14,4), %rsi
          mov       $0, %rax
          call      printf

    skip:
          inc       %r14
          jmp       mask_loop

          mov       $60, %rax
          mov       $0, %rdi
          syscall

          .data
prompt:  .string    "Please enter a number: \n"
printnums: .string  "%d\n"        
nums:     .fill     10, 4, 0
buf:      .zero     100


