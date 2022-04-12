#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "admin.h"
#include "toolbox.h"

int main(int argc, char *argv[])
{
    /* statements */
    unsigned long hashed_pwd;
    FILE* p_password_file;

    /* initialisations */

    /* instructions */
    /*  
    first argument      :   the command name 
    second argument     :   login or reset
    third argument      :   the password (not hashed)
    */

    if(argc != 3)
    {
        return EXIT_FAILURE;
    }

    if(strcmp(argv[1], "login") == 0)
    {
        hashed_pwd = hash(argv[2]);
        if(is_password_valid(hashed_pwd) == TRUE)
        {
            printf("1");
        }
        else
        {
            printf("0");
        }
    }
    else if(strcmp(argv[1], "reset") == 0)
    {
        p_password_file = fopen(PASSWORD_RELATIVE_PATH, "w");
        if(p_password_file == NULL)
        {
            printf("0");
        } 
        hashed_pwd = hash(argv[2]);

        fprintf(p_password_file, "%lu", hashed_pwd);

        if(fclose(p_password_file) == EOF)
        {
            printf("0");
        }
        printf("1");
    }
    else
    {
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}