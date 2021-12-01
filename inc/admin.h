/*
Authors:    Constant ROUX
            Julian TRANI
            Peter PIRIOU--DEZY

Date:       01/12/2021
*/

#ifndef ADMIN_H
#define ADMIN_H

#include "../inc/toolbox.h"

/* password constants */
#define MAX_LENGTH_PASSWORD 10
#define MAX_TRY_PASSWORD 5
#define PASSWORD_CHAR "*"

unsigned long get_hashed_password();
Bool_e is_password_valid(unsigned long in_password);
Bool_e compare_hashed_password(unsigned long in_password, unsigned long saved_password);

#endif