/*
Authors:    Constant ROUX,
            Julian TRANI,
            Peter PIRIOU--DEZY,
            Guillaume ROUSSIN,
            Nelson SANCHEZ
            
Date:       29/11/2021
*/

#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <dirent.h>

#include "../inc/toolbox.h"
#include "../inc/indexation_image.h"
#include "../inc/dynamic_stack.h"

Bool_e save_descriptor_image(FILE* p_base_descriptor_image, Image_descriptor_s* p_descriptor)
{
    /* statements */
    unsigned char i;

    /* instructions */

    if(fprintf(p_base_descriptor_image, "%lu\n", p_descriptor->id) == EOF)
    {
        fprintf(stderr, "Error %d printing id of image descriptor.\n\r", errno);
        return FALSE;
    }

    for(i = 0; i < GRAY_LEVEL; i++)
    {
        if(fprintf(p_base_descriptor_image, "%d\n", p_descriptor->p_histogram[i]) == EOF)
        {
            fprintf(stderr, "Error %d printing histogram value of image descriptor.\n\r", errno);
            return FALSE;
        }
    }
    return TRUE;
}

void create_descriptor_image(char* p_name, unsigned char* p_histogram, Image_descriptor_s* p_descriptor)
{
    /* statements */
    unsigned long hash_code;
    unsigned int i;

    /* initializations */

    /* instructions */
    /* step 1 : hash the file name */
    hash_code = hash(p_name);

    /* step 2 : fill the descriptor struct */
    p_descriptor->id = hash_code;
    for(i = 0; i < GRAY_LEVEL; i++)
    {
        p_descriptor->p_histogram = p_histogram;
    }
}

Bool_e get_parameters_image(Image_s* p_image)
{
    /* statements */
    unsigned int i;

    /* instructions */
    for(i = 0; i < NB_SIZES; i++)
    {
        if(fscanf(p_image->p_image_txt, "%d", &(p_image->a_sizes[i])) == EOF)
        {
            fprintf(stderr, "Error EOF reading %s.\n\r", p_image->p_path);
            return FALSE;
        }

        if(p_image->a_sizes[i] <= 0)
        {
            fprintf(stderr, "Error negative dimension image at %s.\n\r", p_image->p_path);
            return FALSE;
        }

    }
    return TRUE;
}

void do_histogram_image(Image_s* p_image, unsigned char a_quantified_image[], unsigned char a_histogram[])
{
    /* statements */
    unsigned int i;

    /* initializations */
    memset(a_histogram, 0, GRAY_LEVEL * sizeof(unsigned char));

    /* instructions */
    for(i = 0; i < p_image->a_sizes[WIDTH_IDX] * p_image->a_sizes[HEIGHT_IDX]; i++)
    {
        a_histogram[a_quantified_image[i]] += 1; 
    }
}

Bool_e quantify_image(Image_s* p_image, unsigned char a_quantified_image[])
{
    /* statements */
    unsigned char r, g, b;
    unsigned int i;

    /* initializations */

    /* instructions */
    for(i = 0; i < p_image->a_sizes[WIDTH_IDX] * p_image->a_sizes[HEIGHT_IDX]; i++)
    {
        if(p_image->a_sizes[CHANNELS_IDX] == 3)
        {
            if(fscanf(p_image->p_image_txt, "%hhu %hhu %hhu", &r, &g, &b) == EOF)
            {
                fprintf(stderr, "Error EOF reading %s.\n\r", p_image->p_path);
                return FALSE;
            }

            a_quantified_image[i] = ((r & MASK_QUANT) | 
                                    ((g & MASK_QUANT) >> NB_BITS_SHIFTED) | 
                                    ((b & MASK_QUANT) >> (NB_BITS_SHIFTED * 2))) >> NB_BITS_SHIFTED;
        }
        else if(p_image->a_sizes[CHANNELS_IDX] == 1)
        {
            if(fscanf(p_image->p_image_txt, "%hhu", &r) == EOF)
            {
                fprintf(stderr, "Error EOF reading %s.\n\r", p_image->p_path);
                return FALSE;
            }
            a_quantified_image[i] = r / ((PIXEL_MAX_SIZE + 1) / GRAY_LEVEL);
        }
    }
    return TRUE;
}

Bool_e index_image(char* p_path, Image_descriptor_s* p_descriptor)
{
    /* statements */
    FILE* p_image_txt;
    Image_s image;

    /* initializations */
    p_image_txt = fopen(p_path, "r");

    /* instructions */
    if(p_image_txt == NULL)
    {
        fprintf(stderr, "Error %d opening %s.\n\r", errno, p_path);
        return FALSE;
    }
    else
    {
        /* step 1 : get image parameters */
        image.p_path = p_path;
        image.p_image_txt = p_image_txt;
        if(get_parameters_image(&image) == FALSE)
        {
            return FALSE;
        }

        /* step 2 : quantify image */
        unsigned char a_quantified_image[image.a_sizes[WIDTH_IDX] * image.a_sizes[HEIGHT_IDX]];
        if(quantify_image(&image, a_quantified_image) == FALSE)
        {
            return FALSE;
        }

        /* step 3 : do histogram */
        unsigned char a_histogram[GRAY_LEVEL];
        do_histogram_image(&image, a_quantified_image, a_histogram);

        /* step 4 : create descriptor */
        create_descriptor_image(p_path, a_histogram, p_descriptor);
    }

    if(fclose(image.p_image_txt) == EOF)
    {
        fprintf(stderr, "Error %d closing the file %s.\n\r", errno, image.p_path);
        return FALSE;
    }

    return TRUE;
}