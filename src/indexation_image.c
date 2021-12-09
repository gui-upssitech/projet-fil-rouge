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
    unsigned char pixel_unit[RGB_CHANNEL_SIZE];
    unsigned int cursor[RGB_CHANNEL_SIZE];
    unsigned int i, j, k;

    /* initializations */

    /* instructions */
    // printf("height: %d width: %d channels: %d", p_image->a_sizes[0], p_image->a_sizes[1], p_image->a_sizes[2]);
    for(i = 0; i < p_image->a_sizes[HEIGHT_IDX]; i++)
    {
        cursor[0] = i * p_image->a_sizes[WIDTH_IDX];
        cursor[1] = (i + p_image->a_sizes[HEIGHT_IDX]) * p_image->a_sizes[WIDTH_IDX];
        cursor[2] = (i + 2 * p_image->a_sizes[HEIGHT_IDX]) * p_image->a_sizes[WIDTH_IDX];

        for(j = 0; j < p_image->a_sizes[WIDTH_IDX]; j++)
        {       
            if(p_image->a_sizes[CHANNELS_IDX] == RGB_CHANNEL_SIZE)
            {
                for(k = 0; k < RGB_CHANNEL_SIZE; k++)
                {
                    // printf("i:%i j:%i k:%i\n", i, j, k);
                    fseek(p_image->p_image_txt, cursor[k] + j, SEEK_SET);
                    if(fscanf(p_image->p_image_txt, "%hhu ", &pixel_unit[k]) == EOF)
                    {
                        fprintf(stderr, "Error EOF reading %s.\n\r", p_image->p_path);
                        return FALSE;
                    }
                    cursor[k] = ftell(p_image->p_image_txt);
                }

                p_quantified_image[i * p_image->a_sizes[WIDTH_IDX] + j] =   ((pixel_unit[0] & MASK_QUANT) | 
                                                                            ((pixel_unit[1] & MASK_QUANT) >> NB_BITS_SHIFTED) | 
                                                                            ((pixel_unit[2] & MASK_QUANT) >> (NB_BITS_SHIFTED * 2))) >> NB_BITS_SHIFTED;
            }
            else if(p_image->a_sizes[CHANNELS_IDX] == NB_CHANNEL_SIZE)
            {
                if(fscanf(p_image->p_image_txt, "%hhu", &pixel_unit[0]) == EOF)
                {
                    fprintf(stderr, "Error EOF reading %s.\n\r", p_image->p_path);
                    return FALSE;
                }
                p_quantified_image[i * p_image->a_sizes[WIDTH_IDX] + j] = pixel_unit[0] / ((PIXEL_MAX_SIZE + 1) / GRAY_LEVEL);
            }
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