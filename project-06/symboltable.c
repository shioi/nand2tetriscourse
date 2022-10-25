#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "code.h"
#include "parser.h"
#include "symboltable.h"

#define LINE_SIZE 100
#define SYMTABLE_SIZE 101
#define STARTING_ADD 16

Symbol *symboltab[SYMTABLE_SIZE];

char * int_to_string(int);

char * int_to_string(int num) {
  int digits = log10(num)+1;
  char * strnum = (char *)malloc(sizeof(char) * digits+1);
  snprintf( strnum, digits + 1, "%d", num);
  return strnum;
}


//hash function
unsigned hash(char * symbol) {
  unsigned hashval;
  for (hashval=0; *symbol != '\0'; symbol++)
    hashval = *symbol + 31 + hashval;

  return hashval % SYMTABLE_SIZE;
}

//exist and find
Symbol * lookupValue(char * s) {
  Symbol *val;
  val = symboltab[hash(s)];
  for (val = symboltab[hash(s)]; val != NULL; val = val->next){
    if (strcmp(s, val->name) == 0)
      return val;
  }
  return NULL;
}

//adding new entry
Symbol * addSymbol(char *name, char * value) {
  Symbol * np;
  unsigned hashval;
  if((np = lookupValue(name)) == NULL){
    np = (Symbol *)malloc(sizeof(*np));
    if (np == NULL || (np->name = strdup(name)) == NULL)
      return NULL;
    hashval = hash(name);
    np -> next = symboltab[hashval];
    symboltab[hashval] = np;
  }
  else
    free((void *) np->value);

  if((np -> value = strdup(value)) == NULL)
    return NULL;
  return np;
}

//construct new symbol table with primitives
 void construct() {
  addSymbol("R0","0");
  addSymbol("R1","1");
  addSymbol("R2","2");
  addSymbol("R3","3");
  addSymbol("R4","4");
  addSymbol("R5","5");
  addSymbol("R6","6");
  addSymbol("R7","7");
  addSymbol("R8","8");
  addSymbol("R9","9");
  addSymbol("R10","10");
  addSymbol("R11","11");
  addSymbol("R12","12");
  addSymbol("R13","13");
  addSymbol("R14","14");
  addSymbol("R15","15");
  addSymbol("SP","0");
  addSymbol("LCL","1");
  addSymbol("ARG","2");
  addSymbol("THIS","3");
  addSymbol("THAT","4");
  addSymbol ("SCREEN", "16384");
  addSymbol("KBD", "24576");

}

/* build symbol table */
/* 1st pass -> putting labels*/
void firstpass(char * sourcefile) {
  int linenum = -1, instype;
  char  * value, *linestr;
  char * ins;
  Symbol * sm;
  char instruction[LINE_SIZE];
  FILE * sf = fopen(sourcefile,"r");
  if (sf == NULL)
    exit(1);

  while((fgets(instruction,LINE_SIZE,sf)) != NULL) {
    ins = (char *) malloc(sizeof(char) * strlen(instruction));
    ins = remove_spaces(instruction);
    instype = return_instruction_type(ins);
    if(instype == 2) { /* its a label */
      value = (char *)malloc(sizeof(char) * strlen(ins)-1);
      parse_L_instruction(ins, value);
      sm = lookupValue(value);
      if (sm == NULL){
	linestr = int_to_string(linenum+1);
	addSymbol(value,linestr);
	free(linestr);
    }
    free(ins);
    }
    if(instype == 1 || instype == 0)
      linenum++;
  }
}

void secondpass(char * sourcefile) {
  int current_address = STARTING_ADD;
  char * current_add_str;
  Instruction ains;
  char instruction[LINE_SIZE];
  int instype;
  char * ins;
  FILE * sf = fopen(sourcefile,"r");
  if (sf == NULL)
    exit(1);

  while((fgets(instruction,LINE_SIZE,sf)) != NULL) {
    ins = (char *) malloc(sizeof(char) * strlen(instruction));
    ins = remove_spaces(instruction);
    instype = return_instruction_type(ins);
    if(instype == 0) {
      ains = parse_A_instruction(ins);
      if (ains.a.issymbol == 1) /* its a symbol */ {
	if(lookupValue(ains.a.sym) == NULL){
	  current_add_str = int_to_string(current_address);
	  addSymbol(ains.a.sym, current_add_str);
	  current_address++;
	}
      }
    }
    
  }
}


//unit test
/* int main() { */
/*   char * filename = "Max.asm"; */
/*   construct(); */
/*   firstpass(filename); */
/*   secondpass(filename); */
  
/*   printf("%s\n",lookupValue("R0")->value); */
/*   printf("%s\n",lookupValue("R1")->value); */
/*   printf("%s\n",lookupValue("OUTPUT_FIRST")->value); */
/*   printf("%s\n", lookupValue("OUTPUT_D")->value); */
/*   printf("%s\n", lookupValue("INFINITE_LOOP")->value); */
/* } */
