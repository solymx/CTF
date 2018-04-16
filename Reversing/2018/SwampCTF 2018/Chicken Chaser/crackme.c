/* Generated from crackme.cs by the CHICKEN compiler
   http://www.call-cc.org
   2018-03-27 23:39
   Version 4.9.0.1 (stability/4.9.0) (rev 8b3189b)
   linux-unix-gnu-x86-64 [ 64bit manyargs dload ptables ]
   bootstrapped 2014-06-07
   command line: crackme.cs -output-file crackme.c -optimize-level 0
   used units: library eval chicken_2dsyntax extras
*/

#include "chicken.h"

static C_PTABLE_ENTRY *create_ptable(void);
C_noret_decl(C_library_toplevel)
C_externimport void C_ccall C_library_toplevel(C_word c,C_word d,C_word k) C_noret;
C_noret_decl(C_eval_toplevel)
C_externimport void C_ccall C_eval_toplevel(C_word c,C_word d,C_word k) C_noret;
C_noret_decl(C_chicken_2dsyntax_toplevel)
C_externimport void C_ccall C_chicken_2dsyntax_toplevel(C_word c,C_word d,C_word k) C_noret;
C_noret_decl(C_extras_toplevel)
C_externimport void C_ccall C_extras_toplevel(C_word c,C_word d,C_word k) C_noret;

static C_TLS C_word lf[33];
static double C_possibly_force_alignment;
static C_char C_TLS li0[] C_aligned={C_lihdr(0,0,13),40,114,97,110,103,101,32,110,54,32,108,55,41,0,0,0};
static C_char C_TLS li1[] C_aligned={C_lihdr(0,0,14),40,122,105,112,32,108,49,57,32,108,50,49,48,41,0,0};
static C_char C_TLS li2[] C_aligned={C_lihdr(0,0,10),40,97,49,49,57,32,120,49,54,41,0,0,0,0,0,0};
static C_char C_TLS li3[] C_aligned={C_lihdr(0,0,10),40,97,49,50,57,32,120,49,55,41,0,0,0,0,0,0};
static C_char C_TLS li4[] C_aligned={C_lihdr(0,0,10),40,116,111,112,108,101,118,101,108,41,0,0,0,0,0,0};


C_noret_decl(f_69)
static void C_ccall f_69(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_67)
static void C_ccall f_67(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_172)
static void C_ccall f_172(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_63)
static void C_ccall f_63(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_176)
static void C_ccall f_176(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_105)
static void C_ccall f_105(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_180)
static void C_ccall f_180(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_108)
static void C_ccall f_108(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_102)
static void C_ccall f_102(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_188)
static void C_ccall f_188(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_184)
static void C_ccall f_184(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_88)
static void C_ccall f_88(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_81)
static void C_ccall f_81(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_84)
static void C_ccall f_84(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_56)
static void C_ccall f_56(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_118)
static void C_ccall f_118(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_192)
static void C_ccall f_192(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_196)
static void C_ccall f_196(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_77)
static void C_ccall f_77(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(C_toplevel)
C_externexport void C_ccall C_toplevel(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_128)
static void C_ccall f_128(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_120)
static void C_ccall f_120(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_137)
static void C_ccall f_137(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_130)
static void C_ccall f_130(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_96)
static void C_ccall f_96(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_92)
static void C_ccall f_92(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_99)
static void C_ccall f_99(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_144)
static void C_ccall f_144(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_148)
static void C_ccall f_148(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_208)
static void C_ccall f_208(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_204)
static void C_ccall f_204(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_200)
static void C_ccall f_200(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_49)
static void C_ccall f_49(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_47)
static void C_ccall f_47(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_41)
static void C_ccall f_41(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_44)
static void C_ccall f_44(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_154)
static void C_ccall f_154(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_161)
static void C_ccall f_161(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_38)
static void C_ccall f_38(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_165)
static void C_ccall f_165(C_word c,C_word t0,C_word t1) C_noret;

C_noret_decl(tr3)
static void C_fcall tr3(C_proc3 k) C_regparm C_noret;
C_regparm static void C_fcall tr3(C_proc3 k){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
(k)(3,t0,t1,t2);}

C_noret_decl(tr2)
static void C_fcall tr2(C_proc2 k) C_regparm C_noret;
C_regparm static void C_fcall tr2(C_proc2 k){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
(k)(2,t0,t1);}

C_noret_decl(tr4)
static void C_fcall tr4(C_proc4 k) C_regparm C_noret;
C_regparm static void C_fcall tr4(C_proc4 k){
C_word t3=C_pick(0);
C_word t2=C_pick(1);
C_word t1=C_pick(2);
C_word t0=C_pick(3);
C_adjust_stack(-4);
(k)(4,t0,t1,t2,t3);}

/* zip in k45 in k42 in k39 in k36 */
static void C_ccall f_69(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word *a;
if(c!=4) C_bad_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr4,(void*)f_69,4,t0,t1,t2,t3);}
C_trace("crackme.cs:10: map");
((C_proc5)C_fast_retrieve_symbol_proc(lf[5]))(5,*((C_word*)lf[5]+1),t1,C_fast_retrieve(lf[6]),t2,t3);}

/* k65 in k61 in k54 in range in k45 in k42 in k39 in k36 */
static void C_ccall f_67(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("crackme.cs:7: range");
((C_proc4)C_fast_retrieve_proc(*((C_word*)lf[0]+1)))(4,*((C_word*)lf[0]+1),((C_word*)t0)[2],((C_word*)t0)[3],t1);}

/* k170 in k152 in k135 in a129 in k90 in k86 in k82 in k79 in k75 in k45 in k42 in k39 in k36 */
static void C_ccall f_172(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("crackme.cs:32: -");
((C_proc4)C_fast_retrieve_symbol_proc(lf[2]))(4,*((C_word*)lf[2]+1),((C_word*)t0)[2],t1,C_fix(17));}

/* k61 in k54 in range in k45 in k42 in k39 in k36 */
static void C_ccall f_63(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[4],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_63,2,t0,t1);}
t2=t1;
t3=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_67,a[2]=((C_word*)t0)[2],a[3]=t2,tmp=(C_word)a,a+=4,tmp);
C_trace("crackme.cs:7: cons");
((C_proc4)C_fast_retrieve_symbol_proc(lf[1]))(4,*((C_word*)lf[1]+1),t3,((C_word*)t0)[3],((C_word*)t0)[4]);}

/* k174 in k152 in k135 in a129 in k90 in k86 in k82 in k79 in k75 in k45 in k42 in k39 in k36 */
static void C_ccall f_176(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("crackme.cs:32: char->integer");
((C_proc3)C_fast_retrieve_symbol_proc(lf[21]))(3,*((C_word*)lf[21]+1),((C_word*)t0)[2],t1);}

/* k103 in k97 in k94 in k90 in k86 in k82 in k79 in k75 in k45 in k42 in k39 in k36 */
static void C_ccall f_105(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=t1;
((C_proc2)C_fast_retrieve_proc(t2))(2,t2,((C_word*)t0)[2]);}

/* k178 in k135 in a129 in k90 in k86 in k82 in k79 in k75 in k45 in k42 in k39 in k36 */
static void C_ccall f_180(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("crackme.cs:30: =");
((C_proc4)C_fast_retrieve_symbol_proc(lf[23]))(4,*((C_word*)lf[23]+1),((C_word*)t0)[2],t1,C_fix(0));}

/* k106 in k94 in k90 in k86 in k82 in k79 in k75 in k45 in k42 in k39 in k36 */
static void C_ccall f_108(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
if(C_truep(t1)){
C_trace("crackme.cs:43: print");
((C_proc3)C_fast_retrieve_symbol_proc(lf[14]))(3,*((C_word*)lf[14]+1),((C_word*)t0)[2],lf[15]);}
else{
C_trace("crackme.cs:44: print");
((C_proc4)C_fast_retrieve_symbol_proc(lf[14]))(4,*((C_word*)lf[14]+1),((C_word*)t0)[2],lf[16],C_fast_retrieve(lf[12]));}}

/* k100 in k97 in k94 in k90 in k86 in k82 in k79 in k75 in k45 in k42 in k39 in k36 */
static void C_ccall f_102(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,C_SCHEME_UNDEFINED);}

/* k186 in a129 in k90 in k86 in k82 in k79 in k75 in k45 in k42 in k39 in k36 */
static void C_ccall f_188(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("crackme.cs:28: =");
((C_proc4)C_fast_retrieve_symbol_proc(lf[23]))(4,*((C_word*)lf[23]+1),((C_word*)t0)[2],t1,C_fix(0));}

/* k182 in k135 in a129 in k90 in k86 in k82 in k79 in k75 in k45 in k42 in k39 in k36 */
static void C_ccall f_184(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("crackme.cs:30: modulo");
((C_proc4)C_fast_retrieve_symbol_proc(lf[24]))(4,*((C_word*)lf[24]+1),((C_word*)t0)[2],t1,C_fix(5));}

/* k86 in k82 in k79 in k75 in k45 in k42 in k39 in k36 */
static void C_ccall f_88(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_88,2,t0,t1);}
t2=C_mutate2((C_word*)lf[10]+1 /* (set! user-chars ...) */,t1);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_92,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t4=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_200,a[2]=t3,tmp=(C_word)a,a+=3,tmp);
t5=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_204,a[2]=t4,tmp=(C_word)a,a+=3,tmp);
C_trace("crackme.cs:22: length");
((C_proc3)C_fast_retrieve_symbol_proc(lf[25]))(3,*((C_word*)lf[25]+1),t5,C_fast_retrieve(lf[10]));}

/* k79 in k75 in k45 in k42 in k39 in k36 */
static void C_ccall f_81(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_81,2,t0,t1);}
t2=C_mutate2((C_word*)lf[9]+1 /* (set! user-input ...) */,t1);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_84,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t4=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_208,a[2]=t3,tmp=(C_word)a,a+=3,tmp);
C_trace("crackme.cs:19: conc");
((C_proc5)C_fast_retrieve_symbol_proc(lf[27]))(5,*((C_word*)lf[27]+1),t4,lf[28],C_fast_retrieve(lf[9]),lf[29]);}

/* k82 in k79 in k75 in k45 in k42 in k39 in k36 */
static void C_ccall f_84(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_84,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_88,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("crackme.cs:21: string->list");
((C_proc3)C_fast_retrieve_symbol_proc(lf[26]))(3,*((C_word*)lf[26]+1),t2,C_fast_retrieve(lf[9]));}

/* k54 in range in k45 in k42 in k39 in k36 */
static void C_ccall f_56(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[5],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_56,2,t0,t1);}
if(C_truep(t1)){
t2=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,((C_word*)t0)[3]);}
else{
t2=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_63,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[4],a[4]=((C_word*)t0)[3],tmp=(C_word)a,a+=5,tmp);
C_trace("crackme.cs:7: -");
((C_proc4)C_fast_retrieve_symbol_proc(lf[2]))(4,*((C_word*)lf[2]+1),t2,((C_word*)t0)[4],C_fix(1));}}

/* k116 in k90 in k86 in k82 in k79 in k75 in k45 in k42 in k39 in k36 */
static void C_ccall f_118(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("crackme.cs:25: list->string");
((C_proc3)C_fast_retrieve_symbol_proc(lf[18]))(3,*((C_word*)lf[18]+1),((C_word*)t0)[2],t1);}

/* k190 in a129 in k90 in k86 in k82 in k79 in k75 in k45 in k42 in k39 in k36 */
static void C_ccall f_192(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("crackme.cs:28: modulo");
((C_proc4)C_fast_retrieve_symbol_proc(lf[24]))(4,*((C_word*)lf[24]+1),((C_word*)t0)[2],t1,C_fix(2));}

/* k194 in k90 in k86 in k82 in k79 in k75 in k45 in k42 in k39 in k36 */
static void C_ccall f_196(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("crackme.cs:27: map");
((C_proc4)C_fast_retrieve_symbol_proc(lf[5]))(4,*((C_word*)lf[5]+1),((C_word*)t0)[2],((C_word*)t0)[3],t1);}

/* k75 in k45 in k42 in k39 in k36 */
static void C_ccall f_77(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_77,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_81,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("crackme.cs:17: read-line");
((C_proc2)C_fast_retrieve_symbol_proc(lf[30]))(2,*((C_word*)lf[30]+1),t2);}

/* toplevel */
static C_TLS int toplevel_initialized=0;
C_main_entry_point
C_noret_decl(toplevel_trampoline)
static void C_fcall toplevel_trampoline(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall toplevel_trampoline(void *dummy){
C_toplevel(2,C_SCHEME_UNDEFINED,C_restore);}

void C_ccall C_toplevel(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
if(toplevel_initialized) C_kontinue(t1,C_SCHEME_UNDEFINED);
else C_toplevel_entry(C_text("toplevel"));
C_check_nursery_minimum(3);
if(!C_demand(3)){
C_save(t1);
C_reclaim((void*)toplevel_trampoline,NULL);}
toplevel_initialized=1;
if(!C_demand_2(270)){
C_save(t1);
C_rereclaim2(270*sizeof(C_word), 1);
t1=C_restore;}
a=C_alloc(3);
C_initialize_lf(lf,33);
lf[0]=C_h_intern(&lf[0],5,"range");
lf[1]=C_h_intern(&lf[1],4,"cons");
lf[2]=C_h_intern(&lf[2],1,"-");
lf[3]=C_h_intern(&lf[3],1,"<");
lf[4]=C_h_intern(&lf[4],3,"zip");
lf[5]=C_h_intern(&lf[5],3,"map");
lf[6]=C_h_intern(&lf[6],4,"list");
lf[7]=C_h_intern(&lf[7],6,"target");
lf[8]=C_decode_literal(C_heaptop,"\376B\000\000\035g[bV|ds t\077zNDW2\134l\042oNt0oSx\052dW~");
lf[9]=C_h_intern(&lf[9],10,"user-input");
lf[10]=C_h_intern(&lf[10],10,"user-chars");
lf[11]=C_h_intern(&lf[11],9,"user-ints");
lf[12]=C_h_intern(&lf[12],6,"result");
lf[13]=C_h_intern(&lf[13],25,"\003sysimplicit-exit-handler");
lf[14]=C_h_intern(&lf[14],5,"print");
lf[15]=C_decode_literal(C_heaptop,"\376B\000\000\033Success! Submit the flag ;)");
lf[16]=C_decode_literal(C_heaptop,"\376B\000\000\021Nope, try again: ");
lf[17]=C_h_intern(&lf[17],8,"string=\077");
lf[18]=C_h_intern(&lf[18],12,"list->string");
lf[19]=C_h_intern(&lf[19],13,"integer->char");
lf[20]=C_h_intern(&lf[20],1,"+");
lf[21]=C_h_intern(&lf[21],13,"char->integer");
lf[22]=C_h_intern(&lf[22],8,"list-ref");
lf[23]=C_h_intern(&lf[23],1,"=");
lf[24]=C_h_intern(&lf[24],6,"modulo");
lf[25]=C_h_intern(&lf[25],6,"length");
lf[26]=C_h_intern(&lf[26],12,"string->list");
lf[27]=C_h_intern(&lf[27],4,"conc");
lf[28]=C_decode_literal(C_heaptop,"\376B\000\000\015Lets see if \047");
lf[29]=C_decode_literal(C_heaptop,"\376B\000\000\017\047 will do it...");
lf[30]=C_h_intern(&lf[30],9,"read-line");
lf[31]=C_h_intern(&lf[31],12,"write-string");
lf[32]=C_decode_literal(C_heaptop,"\376B\000\000\007Input: ");
C_register_lf2(lf,33,create_ptable());
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_38,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
C_library_toplevel(2,C_SCHEME_UNDEFINED,t2);}

/* k126 in k90 in k86 in k82 in k79 in k75 in k45 in k42 in k39 in k36 */
static void C_ccall f_128(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("crackme.cs:26: map");
((C_proc4)C_fast_retrieve_symbol_proc(lf[5]))(4,*((C_word*)lf[5]+1),((C_word*)t0)[2],((C_word*)t0)[3],t1);}

/* a119 in k90 in k86 in k82 in k79 in k75 in k45 in k42 in k39 in k36 */
static void C_ccall f_120(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word *a;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_120,3,t0,t1,t2);}
C_trace("crackme.cs:26: integer->char");
((C_proc3)C_fast_retrieve_symbol_proc(lf[19]))(3,*((C_word*)lf[19]+1),t1,t2);}

/* k135 in a129 in k90 in k86 in k82 in k79 in k75 in k45 in k42 in k39 in k36 */
static void C_ccall f_137(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word ab[10],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_137,2,t0,t1);}
if(C_truep(t1)){
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_144,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_148,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
C_trace("crackme.cs:29: list-ref");
((C_proc4)C_fast_retrieve_symbol_proc(lf[22]))(4,*((C_word*)lf[22]+1),t3,((C_word*)t0)[3],C_fix(1));}
else{
t2=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_154,a[2]=((C_word*)t0)[2],a[3]=((C_word*)t0)[3],tmp=(C_word)a,a+=4,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_180,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
t4=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_184,a[2]=t3,tmp=(C_word)a,a+=3,tmp);
C_trace("crackme.cs:30: list-ref");
((C_proc4)C_fast_retrieve_symbol_proc(lf[22]))(4,*((C_word*)lf[22]+1),t4,((C_word*)t0)[3],C_fix(0));}}

/* a129 in k90 in k86 in k82 in k79 in k75 in k45 in k42 in k39 in k36 */
static void C_ccall f_130(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[10],*a=ab;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_130,3,t0,t1,t2);}
t3=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_137,a[2]=t1,a[3]=t2,tmp=(C_word)a,a+=4,tmp);
t4=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_188,a[2]=t3,tmp=(C_word)a,a+=3,tmp);
t5=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_192,a[2]=t4,tmp=(C_word)a,a+=3,tmp);
C_trace("crackme.cs:28: list-ref");
((C_proc4)C_fast_retrieve_symbol_proc(lf[22]))(4,*((C_word*)lf[22]+1),t5,t2,C_fix(0));}

/* k94 in k90 in k86 in k82 in k79 in k75 in k45 in k42 in k39 in k36 */
static void C_ccall f_96(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_96,2,t0,t1);}
t2=C_mutate2((C_word*)lf[12]+1 /* (set! result ...) */,t1);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_99,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t4=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_108,a[2]=t3,tmp=(C_word)a,a+=3,tmp);
C_trace("crackme.cs:42: string=?");
((C_proc4)C_fast_retrieve_symbol_proc(lf[17]))(4,*((C_word*)lf[17]+1),t4,C_fast_retrieve(lf[12]),*((C_word*)lf[7]+1));}

/* k90 in k86 in k82 in k79 in k75 in k45 in k42 in k39 in k36 */
static void C_ccall f_92(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word t9;
C_word ab[20],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_92,2,t0,t1);}
t2=C_mutate2((C_word*)lf[11]+1 /* (set! user-ints ...) */,t1);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_96,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t4=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_118,a[2]=t3,tmp=(C_word)a,a+=3,tmp);
t5=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_120,a[2]=((C_word)li2),tmp=(C_word)a,a+=3,tmp);
t6=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_128,a[2]=t4,a[3]=t5,tmp=(C_word)a,a+=4,tmp);
t7=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_130,a[2]=((C_word)li3),tmp=(C_word)a,a+=3,tmp);
t8=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_196,a[2]=t6,a[3]=t7,tmp=(C_word)a,a+=4,tmp);
C_trace("crackme.cs:36: zip");
((C_proc4)C_fast_retrieve_proc(*((C_word*)lf[4]+1)))(4,*((C_word*)lf[4]+1),t8,C_fast_retrieve(lf[11]),C_fast_retrieve(lf[10]));}

/* k97 in k94 in k90 in k86 in k82 in k79 in k75 in k45 in k42 in k39 in k36 */
static void C_ccall f_99(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_99,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_102,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_105,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
C_trace("##sys#implicit-exit-handler");
((C_proc2)C_fast_retrieve_symbol_proc(lf[13]))(2,*((C_word*)lf[13]+1),t3);}

/* k142 in k135 in a129 in k90 in k86 in k82 in k79 in k75 in k45 in k42 in k39 in k36 */
static void C_ccall f_144(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("crackme.cs:29: +");
((C_proc4)C_fast_retrieve_symbol_proc(lf[20]))(4,*((C_word*)lf[20]+1),((C_word*)t0)[2],t1,C_fix(1));}

/* k146 in k135 in a129 in k90 in k86 in k82 in k79 in k75 in k45 in k42 in k39 in k36 */
static void C_ccall f_148(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("crackme.cs:29: char->integer");
((C_proc3)C_fast_retrieve_symbol_proc(lf[21]))(3,*((C_word*)lf[21]+1),((C_word*)t0)[2],t1);}

/* k206 in k79 in k75 in k45 in k42 in k39 in k36 */
static void C_ccall f_208(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("crackme.cs:19: print");
((C_proc3)C_fast_retrieve_symbol_proc(lf[14]))(3,*((C_word*)lf[14]+1),((C_word*)t0)[2],t1);}

/* k202 in k86 in k82 in k79 in k75 in k45 in k42 in k39 in k36 */
static void C_ccall f_204(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("crackme.cs:22: -");
((C_proc4)C_fast_retrieve_symbol_proc(lf[2]))(4,*((C_word*)lf[2]+1),((C_word*)t0)[2],t1,C_fix(1));}

/* k198 in k86 in k82 in k79 in k75 in k45 in k42 in k39 in k36 */
static void C_ccall f_200(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("crackme.cs:22: range");
((C_proc4)C_fast_retrieve_proc(*((C_word*)lf[0]+1)))(4,*((C_word*)lf[0]+1),((C_word*)t0)[2],t1,C_SCHEME_END_OF_LIST);}

/* range in k45 in k42 in k39 in k36 */
static void C_ccall f_49(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word ab[5],*a=ab;
if(c!=4) C_bad_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr4,(void*)f_49,4,t0,t1,t2,t3);}
t4=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_56,a[2]=t1,a[3]=t3,a[4]=t2,tmp=(C_word)a,a+=5,tmp);
C_trace("crackme.cs:5: <");
((C_proc4)C_fast_retrieve_symbol_proc(lf[3]))(4,*((C_word*)lf[3]+1),t4,t2,C_fix(0));}

/* k45 in k42 in k39 in k36 */
static void C_ccall f_47(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_47,2,t0,t1);}
t2=C_mutate2((C_word*)lf[0]+1 /* (set! range ...) */,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_49,a[2]=((C_word)li0),tmp=(C_word)a,a+=3,tmp));
t3=C_mutate2((C_word*)lf[4]+1 /* (set! zip ...) */,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_69,a[2]=((C_word)li1),tmp=(C_word)a,a+=3,tmp));
t4=C_mutate2((C_word*)lf[7]+1 /* (set! target ...) */,lf[8]);
t5=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_77,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("crackme.cs:16: write-string");
((C_proc3)C_fast_retrieve_symbol_proc(lf[31]))(3,*((C_word*)lf[31]+1),t5,lf[32]);}

/* k39 in k36 */
static void C_ccall f_41(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_41,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_44,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_chicken_2dsyntax_toplevel(2,C_SCHEME_UNDEFINED,t2);}

/* k42 in k39 in k36 */
static void C_ccall f_44(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_44,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_47,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_extras_toplevel(2,C_SCHEME_UNDEFINED,t2);}

/* k152 in k135 in a129 in k90 in k86 in k82 in k79 in k75 in k45 in k42 in k39 in k36 */
static void C_ccall f_154(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_154,2,t0,t1);}
if(C_truep(t1)){
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_161,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_165,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
C_trace("crackme.cs:31: list-ref");
((C_proc4)C_fast_retrieve_symbol_proc(lf[22]))(4,*((C_word*)lf[22]+1),t3,((C_word*)t0)[3],C_fix(1));}
else{
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_172,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_176,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
C_trace("crackme.cs:32: list-ref");
((C_proc4)C_fast_retrieve_symbol_proc(lf[22]))(4,*((C_word*)lf[22]+1),t3,((C_word*)t0)[3],C_fix(1));}}

/* k159 in k152 in k135 in a129 in k90 in k86 in k82 in k79 in k75 in k45 in k42 in k39 in k36 */
static void C_ccall f_161(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("crackme.cs:31: -");
((C_proc4)C_fast_retrieve_symbol_proc(lf[2]))(4,*((C_word*)lf[2]+1),((C_word*)t0)[2],t1,C_fix(7));}

/* k36 */
static void C_ccall f_38(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_38,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_41,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_eval_toplevel(2,C_SCHEME_UNDEFINED,t2);}

/* k163 in k152 in k135 in a129 in k90 in k86 in k82 in k79 in k75 in k45 in k42 in k39 in k36 */
static void C_ccall f_165(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("crackme.cs:31: char->integer");
((C_proc3)C_fast_retrieve_symbol_proc(lf[21]))(3,*((C_word*)lf[21]+1),((C_word*)t0)[2],t1);}

#ifdef C_ENABLE_PTABLES
static C_PTABLE_ENTRY ptable[41] = {
{"f_69:crackme_2ecs",(void*)f_69},
{"f_67:crackme_2ecs",(void*)f_67},
{"f_172:crackme_2ecs",(void*)f_172},
{"f_63:crackme_2ecs",(void*)f_63},
{"f_176:crackme_2ecs",(void*)f_176},
{"f_105:crackme_2ecs",(void*)f_105},
{"f_180:crackme_2ecs",(void*)f_180},
{"f_108:crackme_2ecs",(void*)f_108},
{"f_102:crackme_2ecs",(void*)f_102},
{"f_188:crackme_2ecs",(void*)f_188},
{"f_184:crackme_2ecs",(void*)f_184},
{"f_88:crackme_2ecs",(void*)f_88},
{"f_81:crackme_2ecs",(void*)f_81},
{"f_84:crackme_2ecs",(void*)f_84},
{"f_56:crackme_2ecs",(void*)f_56},
{"f_118:crackme_2ecs",(void*)f_118},
{"f_192:crackme_2ecs",(void*)f_192},
{"f_196:crackme_2ecs",(void*)f_196},
{"f_77:crackme_2ecs",(void*)f_77},
{"toplevel:crackme_2ecs",(void*)C_toplevel},
{"f_128:crackme_2ecs",(void*)f_128},
{"f_120:crackme_2ecs",(void*)f_120},
{"f_137:crackme_2ecs",(void*)f_137},
{"f_130:crackme_2ecs",(void*)f_130},
{"f_96:crackme_2ecs",(void*)f_96},
{"f_92:crackme_2ecs",(void*)f_92},
{"f_99:crackme_2ecs",(void*)f_99},
{"f_144:crackme_2ecs",(void*)f_144},
{"f_148:crackme_2ecs",(void*)f_148},
{"f_208:crackme_2ecs",(void*)f_208},
{"f_204:crackme_2ecs",(void*)f_204},
{"f_200:crackme_2ecs",(void*)f_200},
{"f_49:crackme_2ecs",(void*)f_49},
{"f_47:crackme_2ecs",(void*)f_47},
{"f_41:crackme_2ecs",(void*)f_41},
{"f_44:crackme_2ecs",(void*)f_44},
{"f_154:crackme_2ecs",(void*)f_154},
{"f_161:crackme_2ecs",(void*)f_161},
{"f_38:crackme_2ecs",(void*)f_38},
{"f_165:crackme_2ecs",(void*)f_165},
{NULL,NULL}};
#endif

static C_PTABLE_ENTRY *create_ptable(void){
#ifdef C_ENABLE_PTABLES
return ptable;
#else
return NULL;
#endif
}

/*
o|safe globals: (target zip range) 
o|replaced variables: 31 
o|removed binding forms: 15 
o|removed binding forms: 28 
*/
/* end of file */
