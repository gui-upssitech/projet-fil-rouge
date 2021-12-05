/*
Authors:    Constant ROUX,
            Julian TRANI,
            Peter PIRIOU--DEZY,
            Guillaume ROUSSIN,
            Nelson SANCHEZ
            
Date:       29/11/2021
*/

#ifndef INDEXATION_TEXT_H
#define INDEXATION_TEXT_H

/* structure that contains all necessary informations to build the 
text descriptor (...) */
typedef struct
{
    /* unique id of the descriptor based on the hashed file name */
    unsigned long id;

    int provisoire_pour_compiler[4];

} Text_descriptor_s;

#endif