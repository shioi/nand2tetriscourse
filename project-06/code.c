/* generating binary code by taking the parser information
 */

#include <string.h>
#include "code.h"
#include "parser.h"
#include <stdio.h>
#include <stdlib.h>

char * fetch_code(Instruction*);
char * a_code(char *);
char * dest_code(char *);
char * comp_code(char *, char *);
char * jump_code(char *);
char * c_code(Instruction *);
char * concatenate_three(const char *, const char *, const char *);

char * fetch_code(Instruction * inst) {
  //  printf("current instruction is %d\n", inst->ins_type);
  char * generated_code;
  switch(inst->ins_type) {
  case 0: //A instruction
    generated_code = a_code(inst->a.number);
    return generated_code;
    break;
    
  case 1: //C-instruction
    generated_code = c_code(inst);
    return generated_code;
    break;
  }
}

char * a_code(char * inst) {
  char static generated_code[16];
  for (int i=0; i<16;i++)
    generated_code[i] = '0';

  for (int i=0,j=1;i<15;i++) {
    generated_code[j++] = inst[i];
  }
  return generated_code;
}

char * c_code(Instruction * inst) {
  //for the c instuction, construct a hash table
  char * dest, * comp, * jump, a_value, * temp_code;
  a_value = '0';
  dest = dest_code(inst->c.dest);
  jump = jump_code(inst->c.jump);
  comp = comp_code(inst->c.comp,&a_value);
  printf("%s\n",comp);
  temp_code = concatenate_three(comp,dest,jump);

  char * generated_code = (char*)malloc(sizeof(char) * 17);
    if(generated_code){
    generated_code[0] = '1';
    generated_code[1] = '1';
    generated_code[2] = '1';
    generated_code[3] = a_value;
    memcpy(generated_code+4,temp_code, strlen(temp_code));
    }
  return generated_code;
}

char * concatenate_three(const char * a, const char * b , const char * c){
  size_t alen = strlen(a);
  size_t blen = strlen(b);
  size_t clen = strlen(c);
  char * concatenated = (char *)malloc(sizeof(char) * 13);
  if(concatenated) {
    memcpy(concatenated,a, alen);
    memcpy(concatenated+alen,b,blen);
    memcpy(concatenated+alen+blen, c,clen);
  }
  return concatenated;
}

char * dest_code(char * dest_ins) {
  if (dest_ins == NULL)
    return "000";
  else if(strcmp(dest_ins,"M") == 0)
    return "001";
  else if(strcmp(dest_ins,"D")==0)
    return "010";
  else if(strcmp(dest_ins,"MD") == 0)
    return "011";
  else if (strcmp(dest_ins, "A") == 0)
    return "100";
  else if(strcmp(dest_ins, "AM") == 0)
    return "101";
  else if (strcmp(dest_ins,"AD") == 0)
    return "110";
  return "111";
}

char * jump_code(char * jump_ins) {
  if (jump_ins == NULL)
    return "000";
  else if(strcmp(jump_ins, "JGT")==0) 
    return "001";
  else if(strcmp(jump_ins , "JEQ")==0)
    return "010";
  else if(strcmp(jump_ins , "JGE")==0)
    return "011";
  else if (strcmp(jump_ins , "JLT")==0)
    return "100";
  else if(strcmp(jump_ins , "JNE")==0)
    return "101";
  else if(strcmp(jump_ins , "JLE")==0)
    return "110";
  return "111";
}

char * comp_code(char * comp_ins, char * a_value) {
  if (strcmp(comp_ins, "0")==0)
    return "101010";
  else if (strcmp(comp_ins, "1")==0)
    return "111111";
  else if (strcmp(comp_ins, "-1")==0)
    return "111010";
  else if (strcmp(comp_ins,"D")==0)
    return "001100";
  else if(strcmp(comp_ins, "A")==0){
    return "110000";
  }
  else if(strcmp(comp_ins, "M")==0){
    *a_value = '1';
    return "110000";
  }
  else if(strcmp(comp_ins, "!D")==0)
    return "001101";
  else if(strcmp(comp_ins, "!A")==0)
    return "strcmp(110001";
  else if (strcmp(comp_ins, "!M")==0) {
    *a_value = '1';
    return "110001";
  }
  else if(strcmp(comp_ins, "-D")==0)
    return "001111";
  else if(strcmp(comp_ins, "-A")==0)
    return "110011";
  else if(strcmp(comp_ins, "-M")==0){
    *a_value = '1';
    return "110011";
  }
  else if(strcmp(comp_ins ,"D+1")==0)
    return "011111";
  else if(strcmp(comp_ins ,"A+1")==0)
    return "110111";
  else if(strcmp(comp_ins ,"M+1")==0) {
    *a_value = '1';
    return "110111";
  }
  else if(strcmp(comp_ins ,"D-1")==0)
    return "001110";
  else if(strcmp(comp_ins ,"A-1")==0)
    return "110010";
  else if(strcmp(comp_ins ,"M-1")==0) {
    *a_value = '1';
    return "110010";
  }
  else if(strcmp(comp_ins ,"D+A")==0)
    return "000010";
  else if(strcmp(comp_ins ,"D+M")==0){
    *a_value = '1';
    return "000010";
  }
  else if(strcmp(comp_ins ,"D-A")==0)
    return "010011";
  else if(strcmp(comp_ins ,"D-M")==0){
    *a_value = '1';
    return "010011";
  }
  else if(strcmp(comp_ins ,"A-D")==0)
    return "000111";
  else if(strcmp(comp_ins ,"M-D")==0){
    *a_value = '1';
    return "000111";
  }
  else if(strcmp(comp_ins ,"D&A")==0)
    return "000000";
  else if(strcmp(comp_ins ,"D&M")==0){
    *a_value = '1';
    return "000000";
  }
  else if(strcmp(comp_ins ,"D|A")==0)
    return "010101";
  else if(strcmp(comp_ins ,"D|M")==0) {
    *a_value = '1';
    return "010101";
  }
}


