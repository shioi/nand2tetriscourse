/* 1. read line by line
   2. read the 0th character and store in first msb
   3. if msb == 0: A instruction:
   store the next 15 bits in a address variable
 */
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "parser.h"

int return_instruction_type(char *);
Instruction parse_A_instruction(char *);
char * remove_spaces(char *);
char * decimal_to_binary(int, char *);
char * dest_cal(char *);
char * jump_cal(char *);
char * comp_cal(char *);
Instruction parse_C_instruction(char *);

/* finding the instruction type */
int return_instruction_type(char * instruction){
  int count_char = 0;
  if(strlen(instruction) > 1 && instruction[0] != '/') {
    
    switch(instruction[0]) {
      
    case '@':
      return 0;
      break;

    case '(':
      return 2;
      break;

    default:
      return 1;
      break;
    }
    
  }
  return -1;
}

char * remove_spaces(char  * ins) {
  char * new_ins = (char *)malloc(sizeof(char) * strlen(ins));
  int non_space = 0;
  char ch;
  for (int i=0; ins[i] != '\0' && ins[i] != '\n'; i++) {
    if(ins[i] != '\t' && ins[i] != ' ') {
      new_ins[non_space++] = ins[i];
    }
  }
  new_ins[non_space-1] = '\0';
  return new_ins;
}

/* FOR A-INSTRUCTION */
Instruction parse_A_instruction(char * line) {
  Instruction inst;
  char static binary_num[]= {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','\0'};
  char * number_arr = (char *) malloc(sizeof(char) * strlen(line)-1);
  
   inst.ins_type = 0;
   inst.a.msb = line[0];

   //copying
   char ch;
   int i=1,j=0;
   while ((ch=line[i++]) != '\0') {
     number_arr[j++] = ch;
   }
   int number = atoi(number_arr);
   free(number_arr);
   inst.a.number = decimal_to_binary(number, binary_num);
   return inst;

}

/* FOR C-INSTRUCTION */
Instruction parse_C_instruction(char * line) {
  Instruction inst;
  inst.ins_type = 1;
  inst.c.dest = dest_cal(line);
  inst.c.jump = jump_cal(line);
  inst.c.comp = comp_cal(line);
  return inst;
}

char * dest_cal(char * inst) {
  char static dest[4];
  char ch;
  int i,j,flag=0;

  for (i=0; i<strlen(inst); i++) {
    if (inst[i] == '=') {
      flag = 1;
      break;
    }
  }

  if (flag == 0)
    return NULL;

  for (j=0;j<i;j++) {
    dest[j] = inst[j];
  }
  dest[j] = '\0';
  return dest;
}

char * jump_cal(char * inst) {
  //checking if their is a semi-colon. if yes, its position
  char static jmp[4];
  int i,j,flag = 0;
  for (i = 0; i<strlen(inst); i++) {
    if (inst[i] == ';'){
      flag=1;
      break;
    }
  }
  if(flag == 0)		/* no jump statement */
    return NULL;
  i++;
  for (j = 0; j<strlen(inst); j++) {
    jmp[j] = inst[i++];
  }
  jmp[j] = '\0';
  return jmp;
  
}

char * comp_cal(char * inst) {
  //find = and ; position
  int eqpos=-1,semipos;
  semipos = strlen(inst);
  char static calc[4];
  
  for(int i=0; i<strlen(inst); i++) {
    if(inst[i] == '='){
      eqpos = i;
    }

    if(inst[i] == ';') {
      semipos = i;
    }
  }

  //from eqpos to semipos
  int i=0;
  for(eqpos = eqpos+1; eqpos < semipos; eqpos++) {
    calc[i++] = inst[eqpos];
  }
  calc[i] = '\0';
  return calc;
  
}

char * decimal_to_binary(int dec_num, char * binary_num){
  int rem, i = 14;;
  for(int j=0;j<15;j++)
    binary_num[j] = '0';

  while (dec_num > 0) {
    rem = dec_num % 2;
    dec_num /= 2;
    binary_num[i--] = rem + '0';
  }
  return binary_num;
}
