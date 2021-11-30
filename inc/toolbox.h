#ifndef TOOLBOX_H
#define TOOLBOX_H

/* classical boolean type*/
typedef enum {FALSE, TRUE} Bool_e;

Bool_e read_integer(int* p_value);
unsigned long hash(char* p_string);

#endif