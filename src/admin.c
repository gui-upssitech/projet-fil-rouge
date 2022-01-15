/*
Authors:    Constant ROUX,
            Julian TRANI,
            Peter PIRIOU--DEZY,
            Guillaume ROUSSIN,
            Nelson SANCHEZ
            
Date:       29/11/2021
*/

#include "admin.h"

/* NOTE: if the admin menu is left, the password is forgotten and it's necessary to
give again the password to re-enter in the admin menu */

unsigned long get_hashed_password(int* p_code)
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
        
        switch(password[size])
        {
            case '\n':
                fflush(stdout);
                break;
            
            case ESCAPE_KEY:
                break;
            
            case 0x7F:
                if(size > 0)
                {
                    size--;
                }
                printf("\b \b");
                break;
            
            default:
                if(size < MAX_LENGTH_PASSWORD - 1)
                {
                    printf("%s", PASSWORD_CHAR);
                }
                size++;
                break;
        }
        
    } while(size < MAX_LENGTH_PASSWORD && password[size] != '\n' && password[size] != ESCAPE_KEY);

    if(password[size] == ESCAPE_KEY)
    {
        *p_code = -1;
    }
    else
    {
        *p_code = 1;
    }
    password[size + 1] = '\0';
    
    return hash(password);
}

Bool_e is_password_valid(unsigned long in_password)
{
    /* statements */
    FILE* p_password_file;
    unsigned long saved_password;

    /* initializations */
    p_password_file = fopen(PASSWORD_RELATIVE_PATH, "r");

    /* instructions */
    if(p_password_file == NULL)
    {
        fprintf(stderr, "Error %d opening %s.\n\r", errno, PASSWORD_RELATIVE_PATH);
        return FALSE;
    }
    
    if(fscanf(p_password_file, "%lu", &saved_password) == EOF)
    {
        fprintf(stderr, "Error reading password file.\n\r");
    }

    if(fclose(p_password_file) == EOF)
    {
        fprintf(stderr, "Error %d closing the file %s.\n\r", errno, PASSWORD_RELATIVE_PATH);
        return FALSE;
    }

    return compare_hashed_password(in_password, saved_password);
}


Bool_e compare_hashed_password(unsigned long in_password, unsigned long saved_password)
{
    /* instructions */
    return ((in_password == saved_password) ? TRUE : FALSE);
}