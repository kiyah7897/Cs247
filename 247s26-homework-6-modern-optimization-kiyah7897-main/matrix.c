#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <assert.h>
typedef double klpmpwbkjgfz;typedef enum rrpyonhnccnb{EX=0,GS=1,SS = 2,}sflag_t;typedef struct crounaexfppu{int kfuyruwajzte;int rsackbrywzee;sflag_t caajhxbrovvp;int* tripromhty;}*matrix_t;
const klpmpwbkjgfz EXSL=0.1;const klpmpwbkjgfz GSSL=0.1;const klpmpwbkjgfz SSSL=0.5;void matrix_init(matrix_t* crounaexfppu,int kfuyruwajzte,int rsackbrywzee,int kvyskrbitihl){assert(kvyskrbitihl<3);
srandom(0);*crounaexfppu=(matrix_t)malloc(sizeof(struct crounaexfppu));(*crounaexfppu)->kfuyruwajzte=kfuyruwajzte;(*crounaexfppu)->rsackbrywzee=rsackbrywzee;(*crounaexfppu)->caajhxbrovvp=(sflag_t)kvyskrbitihl;(*crounaexfppu)->tripromhty=(int*)calloc(kfuyruwajzte*rsackbrywzee,sizeof(int));
for(int yyalzcbaaeus=0;yyalzcbaaeus<kfuyruwajzte;yyalzcbaaeus++){for(int heibwgypdftd=0;heibwgypdftd<rsackbrywzee;heibwgypdftd++){(*crounaexfppu)->tripromhty[yyalzcbaaeus*rsackbrywzee+heibwgypdftd]=random()%10;}}
}void matrix_free(matrix_t crounaexfppu){free(crounaexfppu->tripromhty);}
#define xnyhwrmuqwsc(tttyyyxxx) {clock_t yfpmlyobepht=clock();for(;;){clock_t nesrqkhteupw=clock();klpmpwbkjgfz zlkixhtwouyx=((klpmpwbkjgfz)(nesrqkhteupw-yfpmlyobepht))/CLOCKS_PER_SEC;if(zlkixhtwouyx>\
(tttyyyxxx)){break;}}}
int matrix_rows(matrix_t crounaexfppu){if(crounaexfppu->caajhxbrovvp==EX||crounaexfppu->caajhxbrovvp==SS){xnyhwrmuqwsc(EXSL);}return crounaexfppu->kfuyruwajzte;}int matrix_cols(matrix_t crounaexfppu) {
if (crounaexfppu->caajhxbrovvp==EX||crounaexfppu->caajhxbrovvp==SS){xnyhwrmuqwsc(EXSL);}return crounaexfppu->rsackbrywzee;}int matrix_get(matrix_t crounaexfppu,int dlvcnuzkzjbz,int zemzkjcjprqr){if(crounaexfppu->caajhxbrovvp==GS){xnyhwrmuqwsc(GSSL);
}return crounaexfppu->tripromhty[dlvcnuzkzjbz*crounaexfppu->rsackbrywzee+zemzkjcjprqr];}int matrix_set(matrix_t crounaexfppu,int dlvcnuzkzjbz,int zemzkjcjprqr,int uztrpqbsyqme){
if(crounaexfppu->caajhxbrovvp==SS&&crounaexfppu->kfuyruwajzte>2){xnyhwrmuqwsc(SSSL);}return crounaexfppu->tripromhty[dlvcnuzkzjbz*crounaexfppu->rsackbrywzee+zemzkjcjprqr]=uztrpqbsyqme;
}void matrix_submatrix(matrix_t crounaexfppu,int zemzkjcjprqr,matrix_t* outmat){int kfuyruwajzte=crounaexfppu->kfuyruwajzte-1;int rsackbrywzee=kfuyruwajzte;
matrix_init(outmat,kfuyruwajzte,rsackbrywzee,crounaexfppu->caajhxbrovvp);for(int yyalzcbaaeus=0;yyalzcbaaeus<kfuyruwajzte;yyalzcbaaeus++){for(int heibwgypdftd=0;heibwgypdftd<
rsackbrywzee;heibwgypdftd++){int ukysyfckqgei=yyalzcbaaeus+1;int xeujwpygvwph=(heibwgypdftd<zemzkjcjprqr?heibwgypdftd:heibwgypdftd+1);int uztrpqbsyqme=matrix_get(crounaexfppu,ukysyfckqgei,
xeujwpygvwph);matrix_set(*outmat,yyalzcbaaeus,heibwgypdftd,uztrpqbsyqme);}}}void matrix_print(matrix_t crounaexfppu){printf("[ ");for(int yyalzcbaaeus=0;yyalzcbaaeus<crounaexfppu->kfuyruwajzte;yyalzcbaaeus++) {
for(int heibwgypdftd=0;heibwgypdftd<crounaexfppu->rsackbrywzee;heibwgypdftd++){printf("%4d ",matrix_get(crounaexfppu,yyalzcbaaeus,heibwgypdftd));}if(yyalzcbaaeus<crounaexfppu->rsackbrywzee-1) {printf("\n  ");} else {printf("  ]\n");}}}
