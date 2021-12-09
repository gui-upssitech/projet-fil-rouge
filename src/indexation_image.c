/*
Authors:    Constant ROUX,
            Julian TRANI,
            Peter PIRIOU--DEZY,
            Guillaume ROUSSIN,
            Nelson SANCHEZ
            
Date:       29/11/2021
*/

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
        if(fprintf(p_base_descriptor_image, "%d ", p_descriptor->p_histogram[i]) == EOF)
        {
            fprintf(stderr, "Error %d printing histogram value of image descriptor.\n\r", errno);
            return FALSE;
        }
    }

    if(fprintf(p_base_descriptor_image, "\n\r") == EOF)
        {
            fprintf(stderr, "Error %d printing new line char in image descriptor.\n\r", errno);
            return FALSE;
        }
    return TRUE;
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

Bool_e do_histogram_image(Image_s* p_image, Image_descriptor_s* p_descriptor, unsigned char* p_quantified_image)
{
    /* statements */
    unsigned int i;

    /* initializatons */
    p_descriptor->p_histogram = (unsigned int*) malloc(GRAY_LEVEL * sizeof(unsigned int));

    /* instructions */
    if(p_descriptor->p_histogram == NULL)
    {
        fprintf(stderr, "Error memory allocation.\n\r");
        return FALSE;
    }
    memset(p_descriptor->p_histogram, 0, GRAY_LEVEL * sizeof(unsigned int));

    for(i = 0; i < p_image->a_sizes[WIDTH_IDX] * p_image->a_sizes[HEIGHT_IDX]; i++)
    {
        p_descriptor->p_histogram[p_quantified_image[i]] += 1; 
    }

    return TRUE;
}

Bool_e quantify_image(Image_s* p_image, unsigned char* p_quantified_image)
{
    /* statements */
    int i, j;
    unsigned char a_color_matrix[RGB_CHANNEL_SIZE][p_image->a_sizes[HEIGHT_IDX] * p_image->a_sizes[WIDTH_IDX]];

    /* instructions */
    /* step 1 : get the color matrix (red, green, blue for rgb images and just gray
    for gray images) */
    for(i = 0; i < RGB_CHANNEL_SIZE && !feof(p_image->p_image_txt); i++)
    {
        for(j = 0; j < p_image->a_sizes[HEIGHT_IDX] * p_image->a_sizes[WIDTH_IDX]; j++)
        {
            if(fscanf(p_image->p_image_txt, "%hhu ", &a_color_matrix[i][j]) == EOF)
            {
                fprintf(stderr, "Error EOF reading %s.\n\r", p_image->p_path);
                return FALSE;
            }
        }
    }

    /* step 2 : quantify the matrix in funciton of the image type */
    for(i = 0; i < p_image->a_sizes[HEIGHT_IDX] * p_image->a_sizes[WIDTH_IDX]; i++)
    {
        if(p_image->a_sizes[CHANNELS_IDX] == RGB_CHANNEL_SIZE)
        {
            p_quantified_image[i] =     ((a_color_matrix[0][i] & MASK_QUANT) | 
                                        ((a_color_matrix[1][i] & MASK_QUANT) >> NB_BITS_SHIFTED) | 
                                        ((a_color_matrix[2][i] & MASK_QUANT) >> (NB_BITS_SHIFTED * 2))) >> NB_BITS_SHIFTED;
        }
        else if(p_image->a_sizes[CHANNELS_IDX] == NB_CHANNEL_SIZE)
        {
            p_quantified_image[i] = a_color_matrix[0][i] / ((PIXEL_MAX_SIZE + 1) / GRAY_LEVEL);
        }
    }
    return TRUE;
}

Bool_e index_image(char* p_path, Image_descriptor_s* p_descriptor)
{
    /* statements */
    FILE* p_image_txt;
    Image_s image;
    unsigned char* p_quantified_image;

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
            printf("Error reading image %s parameters.\n\r", image.p_path);
            return FALSE;
        }

        /* step 2 : quantify image */
        p_quantified_image = (unsigned char*) malloc(image.a_sizes[WIDTH_IDX] * image.a_sizes[HEIGHT_IDX] * sizeof(unsigned char));
        if(p_quantified_image == NULL)
        {
            fprintf(stderr, "Error memory allocation.\n\r");
            return FALSE;
        }

        if(quantify_image(&image, p_quantified_image) == FALSE)
        {
            fprintf(stderr, "Error during quantification of %s.\n\r", image.p_path);
            return FALSE;
        }

        /* step 3 : do histogram */
        if(do_histogram_image(&image, p_descriptor, p_quantified_image) == FALSE)
        {
            fprintf(stderr, "Error during histogram creation of %s.\n\r", image.p_path);
            return FALSE;
        }

        /* step 4 : generate id */
        p_descriptor->id = hash(image.p_path);
    }

    if(fclose(image.p_image_txt) == EOF)
    {
        fprintf(stderr, "Error %d closing the file %s.\n\r", errno, image.p_path);
        return FALSE;
    }

    return TRUE;
}