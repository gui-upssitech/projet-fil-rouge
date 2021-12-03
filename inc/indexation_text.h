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

    float provisoire_pour_compiler;

} Text_descriptor_s;

#endif