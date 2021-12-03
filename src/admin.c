/*
Authors:    Constant ROUX
            Julian TRANI
            Peter PIRIOU--DEZY

Date:       01/12/2021
*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "../inc/admin.h"
#include "../inc/toolbox.h"

/* NOTE: if the admin menu is left, the password is forgotten and it's necessary to
give again the password to re-enter in the admin menu */

unsigned long get_hashed_password()
{
    /* statements */
    char password[MAX_LENGTH_PASSWORD + 1];
    unsigned char size;
    
    /* initializations */
    size = 0;

    /* instructions */
    do 
    {
        password[size] = getch();
        
        if(password[size] != '\n')
        {
            printf("%s", PASSWORD_CHAR);
        }
        size++;
    } while(size < MAX_LENGTH_PASSWORD && password[size - 1] != '\n');
    password[size] = '\0';
    
    return hash(password);
}

Bool_e is_password_valid(unsigned long in_password)
{
    /* statements */
    FILE* password_file;
    unsigned long saved_password;

    /* initializations */
    password_file = fopen(PASSWORD_RELATIVE_PATH, "r");

    /* instructions */
    if(password_file == NULL)
    {
        printf("Error %d opening %s.\n\r", errno, PASSWORD_RELATIVE_PATH);
        return FALSE;
    }
    
    if(fscanf(password_file, "%lu", &saved_password) == EOF)
    {
        printf("Error reading password file.\n\r");
    }

    if(fclose(password_file) == EOF)
    {
        printf("Error %d closing the file %s.\n\r", errno, PASSWORD_RELATIVE_PATH);
        return FALSE;
    }

    return compare_hashed_password(in_password, saved_password);
}


Bool_e compare_hashed_password(unsigned long in_password, unsigned long saved_password)
{
    /* instructions */
    return ((in_password == saved_password) ? TRUE : FALSE);
}