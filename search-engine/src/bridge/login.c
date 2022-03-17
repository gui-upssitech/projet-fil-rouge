#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "admin.h"
#include "toolbox.h"

int main(int argc, char *argv[])
{
    /* statements */
    unsigned long hashed_pwd;

    /* initialisations */

    /* instructions */
    /*  
    first argument      :   the command name 
    second argument     :   the password (not hashed)
    */

    if(argc != 2)
    {
        return EXIT_FAILURE;
    }

    hashed_pwd = hash(argv[1]);
    if(is_password_valid(hashed_pwd) == TRUE)
    {
        printf("1");
    }
    else
    {
        printf("0");
    }

    return EXIT_SUCCESS;
}