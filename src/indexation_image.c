/*
Authors:    Constant ROUX, 
            Peter PIRIOU--DEZY,
            Julian TRANI

Date:       29/11/2021
*/

#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <dirent.h>
#include <string.h>

#include "../inc/toolbox.h"
#include "../inc/indexation_image.h"
#include "../inc/dynamic_stack.h"

Bool_e automatic_image_indexation()
{
    /* files statements */
    FILE* p_index_table;

    /* dir explorer statements */
    struct dirent* p_dir;
    DIR* p_d;

    /* descriptors statements */
    Image_descriptor_s image_descriptor;
    Dynamic_stack_p p_dynamic_stack;
    Unit_u unit;

    /* initializations */
    p_dynamic_stack = init_dynamic_stack();
    p_index_table = fopen(INDEX_TABLE_PATH, "a+");

    /* instructions */
    if(p_index_table == NULL)
    {
        printf("Error %d opening %s.\n\r", errno, INDEX_TABLE_PATH);
        return FALSE;
    }

    /* NB images first */
    p_d = opendir(NB_BASE_PATH);
    if(p_d)
    {
        while((p_dir = readdir(p_d)) != NULL)
        {
            /* step 1 : check if the read file contains the string ".txt"*/
            if(strstr(p_dir->d_name, TEXT_EXTENSION) != NULL)
            {
                /* step 2 : check if the index table contains the file being processed */
                if(file_contains_substring(p_index_table, p_dir->d_name) == FALSE)
                {
                    /* step 3 : create the descriptor of the file */
                    if(index_image(str_concat(NB_BASE_PATH, p_dir->d_name), &image_descriptor) == FALSE)
                    {
                        printf("Error creating file descriptor.\n\r");
                        return FALSE;
                    }
                    
                    /* step 4 : add the new descriptor in the stack */
                    unit.image_descriptor = image_descriptor;
                    p_dynamic_stack = add_unit_dynamic_stack(p_dynamic_stack, unit);

                    /* step 5 : add the new file in the index table */
                    fprintf(p_index_table, "%s\n", p_dir->d_name);
                }
            }
        }
        closedir(p_d);
    }
    else
    {
        printf("Error %d opening %s.\n\r", errno, INDEX_TABLE_PATH);
        return FALSE;
    }

    if(fclose(p_index_table) == EOF)
    {
        printf("Error %d closing the file %s.\n\r", errno, INDEX_TABLE_PATH);
        return FALSE;
    }
    return TRUE;
}

Bool_e save_descriptor_image(FILE* p_base_descriptor_image, Image_descriptor_s* p_descriptor)
{
    /* statements */
    unsigned char i;

    /* instructions */

    if(fprintf(p_base_descriptor_image, "%lu\n", p_descriptor->id) == EOF)
    {
        printf("Error %d printing id of image descriptor.\n\r", errno);
        return FALSE;
    }

    for(i = 0; i < GRAY_LEVEL; i++)
    {
        if(fprintf(p_base_descriptor_image, "%d\n", p_descriptor->p_histogram[i]) == EOF)
        {
            printf("Error %d printing histogram value of image descriptor.\n\r", errno);
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
            printf("Error EOF reading %s.\n\r", p_image->p_path);
            return FALSE;
        }

        if(p_image->a_sizes[i] <= 0)
        {
            printf("Error negative dimension image at %s.\n\r", p_image->p_path);
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
                printf("Error EOF reading %s.\n\r", p_image->p_path);
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
                printf("Error EOF reading %s.\n\r", p_image->p_path);
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
        printf("Error %d opening %s.\n\r", errno, p_path);
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
        printf("Error %d closing the file %s.\n\r", errno, image.p_path);
        return FALSE;
    }

    return TRUE;
}