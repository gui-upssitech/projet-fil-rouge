#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>

#include "../inc/toolbox.h"

/* source: https://stackoverflow.com/questions/421860/capture-characters-from-standard-input-without-waiting-for-enter-to-be-pressed */
char getch() 
{
    char buf = 0;
    struct termios old = {0};
    if (tcgetattr(0, &old) < 0)
    { 
        perror("tcsetattr()");
    }
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if (tcsetattr(0, TCSANOW, &old) < 0)
    { 
        perror("tcsetattr ICANON");
    }
    if (read(0, &buf, 1) < 0)
    {
        perror ("read()");
    }
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if (tcsetattr(0, TCSADRAIN, &old) < 0)
    { 
        perror ("tcsetattr ~ICANON");
    }
    return (buf);
}

void fflush_stdin()
{
    /* declarations */
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