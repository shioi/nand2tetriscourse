#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

typedef struct Symbol{
  struct Symbol * next;			/* next entry */
  char * name;			/* symbol to be replaced */
  char * value;			/* replacement text */
}Symbol;



/* function declaration */
unsigned hash(char *);
Symbol * lookupValue(char *);
Symbol * addSymbol(char *, char *);
void construct();
void firstpass(char *);
void secondpass(char *);

#endif
