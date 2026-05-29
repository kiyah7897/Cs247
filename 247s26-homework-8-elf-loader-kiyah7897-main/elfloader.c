#include <stdio.h>
#include "elfheader.h"
#include <stdlib.h>
#include <math.h>
#include <sys/mman.h>

int main(int argc, char** argv) {
    // Remove this code and enter your own
    if(argc !=4 ){
        fprintf(stderr, "Usage: ./elfloader file arg1 arg2\n");
        exit(1);
    }

    FILE *f = fopen(argv[1], "rb");
    if( f == NULL){
        fprintf(stderr, "File cannot be opened\n");
        exit(2);
    }
    Elf64_Ehdr elfheader;
    fread(&elfheader , sizeof(Elf64_Ehdr), 1 , f);
    if(elfheader.e_ident[0] != 0x7F || elfheader.e_ident[1] != 'E'|| elfheader.e_ident[2] != 'L'|| elfheader.e_ident[3] != 'F'){
        fprintf(stderr, "File is not a ELf file\n");
        exit(2);
    }
    fseek(f, elfheader.e_phoff, SEEK_SET);

    Elf64_Phdr progheader;
    int found = 0;
    int num1 = atoi(argv[2]);
    int num2 = atoi(argv[3]);
    for(int i = 0; i < elfheader.e_phnum; i++){
    fread(&progheader , sizeof(Elf64_Phdr),1, f);
        if(progheader.p_type == PT_LOAD && progheader.p_flags & PF_X){
        Elf64_Off offset = progheader.p_offset;
        Elf64_Addr virtaddress = progheader.p_vaddr;
        uint64_t size = progheader.p_memsz;
        found = 1;

        void* codep = mmap(NULL, size, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_ANONYMOUS | MAP_PRIVATE, 0, 0);
            if( codep == MAP_FAILED){
            fprintf(stderr, "Failed to allocate memory\n");
            exit(2);
            }
            fseek(f , offset , SEEK_SET);
            fread(codep , size , 1 ,f);
            Elf64_Addr entryoffset = elfheader.e_entry - virtaddress;
            unsigned int (*mainfunc)(int, int) = codep + entryoffset;
            int answer = (*mainfunc)(num1, num2);
            munmap(codep ,size);
            printf("Answer=%d\n" , answer);
        }
    }
    if(found != 1){
        fprintf(stderr, "Program header was not found\n");
        exit(3);
    } 
    fclose(f);
    return 0;
}
