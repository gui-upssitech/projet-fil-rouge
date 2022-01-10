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

#include "admin.h"
#include "toolbox.h"

int main(void)
{
    /* statements */
    unsigned long password;
    Bool_e ret_value;

    /* initializations */


    /* instructions */
    printf("test login :\n\r");
    password = get_hashed_password();
    ret_value = is_password_valid(password);
    printf("\n\ris valid : %s\n\r", ret_value == 0 ? "FAUX" : "VRAI");
    printf("\n\r%lu %lu", hash("root"), hash("root\n"));
    return EXIT_SUCCESS;
}