/*
Authors:    Constant ROUX,
            Julian TRANI,
            Peter PIRIOU--DEZY,
            Guillaume ROUSSIN,
            Nelson SANCHEZ
            
Date:       29/11/2021
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <string.h>

#include "toolbox.h"

unsigned short shift(unsigned char a, int b)
{
    return ((b < 0) ? (((unsigned short) a) >> -b) : (((unsigned short) a) << b));
}

unsigned int get_bytes_size_file(FILE* p_file)
{
    /* statements */
    int bytes;

    /* instructions */
    fseek(p_file, 0, SEEK_END);
    bytes = ftell(p_file);
    fseek(p_file, 0, SEEK_SET);
    printf("size: %d\n", bytes);
    return bytes;
}

char* str_concat(char* str1, char* str2)
{
    /* statements */
    char* ret;
    unsigned int size1, size2;
    unsigned int i;

    /* initializations */
    size1 = get_array_size_from_pointer(str1);
    size2 = get_array_size_from_pointer(str2);
    ret = (char *) malloc((size1 + size2 + 1) * sizeof(char));

    /* instructions */
    for(i = 0; i < size1; i++)
        *(ret + i) = *(str1 + i);

    for(i = 0; i < size2; i++)
        *(ret + size1 + i) = *(str2 + i);
    
    *(ret + size1 + i) = '\0';
    
    return ret;
}

Bool_e file_contains_substring(FILE* p_file, char* p_str)
{
    /* statements */
    char* p_line;
    size_t len;
    ssize_t read;

    /* initializations */
    p_line = NULL;
    len = 0;

    /* instructions */
    while(!feof(p_file))
    {
        if((read = getline(&p_line, &len, p_file)) != -1)
        {
            if(strstr(p_line, p_str) != NULL)
            {
                return TRUE;
            }
        }
    }

    if(p_line != NULL)
    {
        free(p_line);
    }

    return FALSE;
}

char getch(void)
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO);
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    system("stty -echo");
    ch = getchar();
    system("stty echo");
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}

void fflush_stdin()
{
    /* statements */
    char c;

    /* instructions */
    for(c = 0; c != '\n' && c != EOF; c = getchar());
}

unsigned int get_array_size_from_pointer(char* p_array)
{
    /* statements */
    unsigned int size;
    char c;

    /* initializations */
    size = 0;

    /* instructions */
    while((c = *p_array++) != '\0')
    {
        size++;
    }
    return size;
}

/* source: https://stackoverflow.com/questions/7666509/hash-function-for-string */
unsigned long hash(char* p_string)
{
    /* statements */
    unsigned long hash = 5381;
    int c;

    /* instructions */
    while ((c = *p_string++))
    {
        /* hash * 33 + c */
        hash = ((hash << 5) + hash) + c;
    }

    return hash;
}

Bool_e read_integer(int* p_value)
{
    /* statements */
    Bool_e return_value;

    /* initializations */

    /* instructions */
    if(scanf("%d", p_value))
    {
        return_value = TRUE;
    }
    else
    {
        return_value = FALSE;
    }
    return return_value;
}