/*
Authors:    Constant ROUX,
            Peter PIRIOU--DEZY
            
Date:       29/11/2021
*/

#ifndef TOOLBOX_H
#define TOOLBOX_H

#include <stdio.h>

/* classical boolean type*/
typedef enum {FALSE, TRUE} Bool_e;

Bool_e read_integer(int* p_value);
unsigned long hash(char* p_string);
unsigned int get_array_size_from_pointer(char* p_array);
void fflush_stdin();
char getch();
Bool_e file_contains_substring(FILE* p_file, char* p_str);
char* str_concat(char* str1, char* str2);

#endif