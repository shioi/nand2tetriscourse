#ifndef PARSER_H
#define PARSER_H

typedef struct {
  char * comp;
  char * dest;
  char * jump;
}cinstruction;

typedef struct {
  char msb;
  char * number ;
}ainstruction;

typedef struct {
  int ins_type;
  union {
    cinstruction c;
    ainstruction a;
  };
} Instruction;

int return_instruction_type(char *);
Instruction parse_A_instruction(char *);
char * remove_spaces(char *);
Instruction  parse_C_instruction(char *);

#endif
