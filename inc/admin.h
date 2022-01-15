/*
Authors:    Constant ROUX,
            Julian TRANI,
            Peter PIRIOU--DEZY,
            Guillaume ROUSSIN
            
            
Date:       29/11/2021
*/

#ifndef ADMIN_H
#define ADMIN_H

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "toolbox.h"

/* password constants */
#define MAX_LENGTH_PASSWORD 20
#define MAX_TRY_PASSWORD 5
#define PASSWORD_CHAR "*"

/* path constants */
#define PASSWORD_RELATIVE_PATH "admin/password.tpscrt"

unsigned long get_hashed_password(int* p_code);

/**
 * @brief Check if the input hashed password is equals to the admin password in the password.tpscrt file.
 * 
 * @param in_password the hashed input password.
 * @return Bool_e TRUE if password is valid, FALSE else.
 */
Bool_e is_password_valid(unsigned long in_password);

/**
 * @brief Compare two hashed passwords
 * 
 * @param in_password the input hashed password.
 * @param saved_password the saved hashed password.
 * @return Bool_e TRUE if password are equals, FALSE else.
 */
Bool_e compare_hashed_password(unsigned long in_password, unsigned long saved_password);

#endif