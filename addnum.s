# Writes Read two single digit numbers from the user, add them and display the result. Runs on 64-bit Linux only.
# To assemble and run:
#
#     gcc -g -no-pie -z noexecstack addnum.s -o addnum
# ----------------------------------------------------------------------------------------

          .global    main

          .text
main:     mov       $1, %rax                # system call for write
          mov       $1, %rdi                # file handle 1 is stdout
          mov       $firstline, %rsi          # address of string to output
          mov       $24, %rdx               # number of bytes
          syscall                           # invoke operating system to do the write
          
          mov       $0, %rax                # system call for read
          mov       $0, %rdi                # file handle 0 is stdin
          mov       $buf, %rsi          # address of string to output
          mov       $100, %rdx               # number of bytes
          syscall    

          mov       $buf, %rdi              #store the first number 
          call      atoi                    #convert it to  a int
          mov       %rax, %r12              #save the first number in r12

          mov       $1, %rax                # system call for write
          mov       $1, %rdi                # file handle 1 is stdout
          mov       $secondline, %rsi          # address of string to output
          mov       $24, %rdx               # number of bytes
          syscall                           # invoke operating system to do the write

          mov       $0, %rax                # system call for read
          mov       $0, %rdi                # file handle 0 is stdin
          mov       $buf, %rsi          # address of string to output
          mov       $100, %rdx               # number of bytes
          syscall                         

          mov       $buf,%rdi
          call      atoi
          mov       %rax, %r13              #save second number 
          
          add       %r12, %r13
          add       $48,  %r13
          mov       %r13b, result

          mov       $1, %rax     
          mov       $1, %rdi
          mov       $sum, %rsi
          mov       $13, %rdx        
          syscall

          mov        $1, %rax
          mov        $1, %rdi
          mov        $result, %rsi
          mov        $1, %rdx
          syscall
         
          mov        $1, %rax
          mov        $1, %rdi
          mov        $newline, %rsi
          mov        $1, %rdx
          syscall

          mov       $60, %rax               # system call for exit
          mov       $0, %rdi                # exit code 0
          syscall                           # invoke operating system to exit


          .data
firstline:  .asciz    "Please enter a number: \n"
secondline: .asciz    "Please enter a number: \n"
sum:        .asciz    "The sum is: "
newline:    .asciz    "\n"
result:     .zero      2
buf:        .zero      100
