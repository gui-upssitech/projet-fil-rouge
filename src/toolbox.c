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
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "toolbox.h"

/* source : https://stackoverflow.com/questions/4553012/checking-if-a-file-is-a-directory-or-just-a-file */
Bool_e is_regular_file(const char *path)
{
    /* statements */
    struct stat path_stat;

    /* initializations */
    stat(path, &path_stat);

    /* instructions */
    return S_ISREG(path_stat.st_mode) > 0 ? TRUE : FALSE;
}

Bool_e is_extension_file(const char *path, char *extension)
{
    /* statements */
    char *dot;
    char *read_extension;

    /* instructions */
    dot = strrchr(path, '.');
    if (!dot || dot == path)
    {
        return FALSE;
    }

    read_extension = dot + 1;

    if (strcmp(read_extension, extension) != 0)
    {
        return FALSE;
    }

    return TRUE;
}

Bool_e read_path(char **path, int *code)
{
    /* statements */
    int i;
    char c;

    /* initializations */
    i = 0;
    *path = (char *)malloc(sizeof(char));

    /* instructions */
    if (*path == NULL)
    {
        fprintf(stderr, "Error memory allocation.\n\r");
        return FALSE;
    }

    do
    {
        c = getch();
        printf("%c", c);
        (*path)[i] = c;
        if ((*path)[i] == 0x7F) // TO DO
        {
            if (i > 0)
            {
                i--;
            }
            printf("\b \b");
            continue;
        }

        i++;
        *path = (char *)realloc(*path, (i + 1) * sizeof(char));
        if (*path == NULL)
        {
            fprintf(stderr, "Error memory reallocation.\n\r");
            return FALSE;
        }

    } while (c != ESCAPE_KEY && c != ENTER_KEY);

    (*path)[i - 1] = '\0';

    if (c == ESCAPE_KEY)
    {
        *code = -1;
    }
    else
    {
        *code = 0;
    }

    return TRUE;
}

unsigned short shift(unsigned char a, int b)
{
    return ((b < 0) ? (((unsigned short)a) >> -b) : (((unsigned short)a) << b));
}

unsigned int get_bytes_size_file(FILE *p_file)
{
    /* statements */
    int bytes;

    /* instructions */
    fseek(p_file, 0, SEEK_END);
    bytes = ftell(p_file);
    fseek(p_file, 0, SEEK_SET);
    return bytes;
}

char* str_concat(char *str1, char *str2)
{
    /* statements */
    char *ret;
    unsigned int size1, size2;
    unsigned int i;

    /* initializations */
    size1 = get_array_size_from_pointer(str1);
    size2 = get_array_size_from_pointer(str2);
    ret = (char*) malloc((size1 + size2 + 1) * sizeof(char));

    if (ret != NULL)
    {
        /* instructions */
        for (i = 0; i < size1; i++)
            *(ret + i) = *(str1 + i);

        for (i = 0; i < size2; i++)
            *(ret + size1 + i) = *(str2 + i);

        *(ret + size1 + i) = '\0';
    }

    return ret;
}

Bool_e file_contains_substring(FILE *p_file, char *p_str, char **ret_line)
{
    /* statements */
    size_t len;
    ssize_t read;
    char *p_line;

    /* initializations */
    p_line = NULL;
    len = 0;

    /* instructions */
    if(p_file != NULL)
    {
        while (!feof(p_file))
        {
            if ((read = getline(&p_line, &len, p_file)) != -1)
            {
                if (strstr(p_line, p_str) != NULL)
                {
                    if (ret_line != NULL)
                    {
                        *ret_line = p_line;
                    }
                    return TRUE;
                }
            }
        }
    }

    return FALSE;
}

char getch(void)
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr(STDIN_FILENO, &oldattr);
    newattr = oldattr;
    newattr.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
    system("stty -echo");
    ch = getchar();
    system("stty echo");
    tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
    return ch;
}

void fflush_stdin(void)
{
    /* statements */
    char c;

    /* instructions */
    for (c = 0; c != '\n' && c != EOF; c = getchar())
        ;
}

unsigned int get_array_size_from_pointer(const char *p_array)
{
    /* statements */
    unsigned int size;
    char c;

    /* initializations */
    size = 0;

    /* instructions */
    while ((c = *p_array++) != '\0')
    {
        size++;
    }
    return size;
}

unsigned long hash(char *p_string)
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

Bool_e read_integer(long *p_value)
{
    /* statements */
    char a_string[MAX_MEMORY_STRING];
    char *p_end;

    /* initializations */

    /* instructions */
    if (scanf("%s", a_string) != 1)
    {
        return FALSE;
    }

    *p_value = strtol(a_string, &p_end, 10);
    if ((*p_value == 0L && p_end == a_string) || errno == ERANGE)
    {
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}