# Read a number from the keyboard and display it on the screen. Runs on 64-bit Linux only.
# To assemble and run:
#
#     gcc -g -no-pie -z noexecstack readnum.s -o readnum
# ----------------------------------------------------------------------------------------

          .global    main

          .text
main:     mov       $1, %rax                # system call for write "please eneter"
          mov       $1, %rdi                # file handle 1 is stdout
          mov       $input, %rsi          # address of string to output
          mov       $24, %rdx               # number of bytes
          syscall                           # invoke operating system to do the write

          mov       $0, %rax                #read users input 
          mov       $0, %rdi                # handle 0 stdin
          mov       $buf, %rsi           # adress of string to output
          mov       $100, %rdx
          syscall                       # invoke operating syustem to read into buffer
          
          mov       %rax, %r12          # save the count for later
          mov       $1, %rax            # system call for write "you have entered" 
          mov       $1, %rdi
          mov       $output, %rsi
          mov       $18, %rdx
          syscall
          
          mov       $1, %rax
          mov       $1, %rdi
          mov       $buf, %rsi
          mov       %r12, %rdx
          syscall 

          mov       $60, %rax               # system call for exit
          mov       $0, %rdi                # exit code 0
          syscall                           # invoke operating system to exit

          .data
input:  .ascii    "Please enter a number: \n"
output:  .ascii    "You have entered: \n"

buf:      .zero     100

