/*
Authors:    Constant ROUX
            
Date:       29/11/2021
*/

#ifndef DESCRIPTOR_H
#define DESCRIPTOR_H

/* structure that contains all necessary informations to build the 
text descriptor (...) */
typedef struct
{
    int provisoire_pour_compiler;

} Text_descriptor_s;

/* structure that contains all necessary informations to build the 
image descriptor (id and histogram) */
typedef struct
{
    /* unique id of the descriptor based on the hashed file name */
    unsigned long id;

    /* histogram of the file (size of 6 bits) */
    unsigned char* p_histogram;

} Image_descriptor_s;

/* structure that contains all necessary informations to build the 
audio descriptor (...) */
typedef struct
{

} Audio_descriptor_s;

#endif