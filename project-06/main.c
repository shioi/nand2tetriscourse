#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include "parser.h"
#include "code.h"
#include "symboltable.h"

#define LINE_SIZE  120
#define WORD_SIZE 16

Instruction parse_lines(int, char *);
void read_line(char *);
int drive(char *, FILE * );
void write_to_file(FILE *, char *);
FILE * create_new_file(char *);
void constructsymtable(char *);

void constructsymtable(char * filename) {
  construct();
  firstpass(filename);
  secondpass(filename);
}

FILE * create_new_file(char * oriname) {
  char * newname = (char *) malloc(sizeof(char)* strlen(oriname)+2);
  int i;
  for (i=0; oriname[i]!='.';i++){
    newname[i] = oriname[i];
  }
  newname[i] = oriname[i];
  newname[++i] = 'h';
  newname[++i] = 'a';
  newname[++i] = 'c';
  newname[++i] = 'k';
  newname[++i] = '\0';

  FILE * hackfile = fopen(newname,"w");
  if(hackfile == NULL)
    exit(1);

  return hackfile;
}

void read_line(char * sourcefile) {

  FILE * fp, *  hackfile;
  char current_line[LINE_SIZE];
  hackfile  = create_new_file(sourcefile);
  
  if ((fp = fopen(sourcefile, "r")) != NULL)
    {
      while((fgets(current_line, LINE_SIZE, fp)) != NULL){
	drive(current_line, hackfile);
  }
    }
}

int drive(char * current_line, FILE * hackfile) {
  Instruction parsed_ins;
  int instype;
  char * instruction;
  char * generated_code;
  
  instruction = (char *) malloc(sizeof(char) * strlen(current_line));
  instruction = remove_spaces(current_line);
  printf("%s\n",instruction);
  
  //parsing
  instype = return_instruction_type(instruction);
  /* TODO: For Lables, include Lables too for the Symbol module */
  if (instype != 0 && instype != 1)
    return -1;
  
  parsed_ins = parse_lines(instype, instruction);

  free(instruction);
  
  //generating code
  generated_code = fetch_code(&parsed_ins);
  write_to_file(hackfile, generated_code);
}

void write_to_file(FILE * hf, char * line) {
  fprintf(hf, "%s\n",line);
}

Instruction parse_lines(int type, char * line) {
  Instruction parsed_ins;
  if (type == 0) {
    parsed_ins = parse_A_instruction(line);
  }
  else if (type == 1) {
    parsed_ins = parse_C_instruction(line);
  }
  return parsed_ins;
}


int main(int argc, char ** argv)  {
  
  if (argc != 2){
    fprintf(stderr, "Error! %s <filename.asm>\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  //TODO: Checking for the right extension for the files
  constructsymtable(argv[1]);
  read_line(argv[1]);
}

