#ifndef DESCRIPTOR_H
#define DESCRIPTOR_H

#include "../inc/indexation_image.h"

/* structure that contains all necessary informations to build the 
descriptor (id and histogram) */
typedef struct
{
    /* unique id of the descriptor based on the hashed file name */
    unsigned long id;

    /* histogram of the file (size of 6 bits) */
    unsigned char* p_histogram;

} Image_descriptor_s;

#endif