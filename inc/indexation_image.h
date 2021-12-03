/*
Authors:    Constant ROUX,
            Julian TRANI,
            Peter PIRIOU--DEZY
            
Date:       29/11/2021
*/

#ifndef INDEXATION_IMAGE_H
#define INDEXATION_IMAGE_H

#include <stdio.h>

#include "descriptor.h"
#include "toolbox.h"


/* descriptor file path constants */
#define INDEX_TABLE_PATH "descriptors/image/image_index_table.txt"
#define BASE_IMAGE_DESCRIPTOR_PATH "descriptors/image/base_image_descriptor.txt"

/* data file path constants */
#define NB_BASE_PATH "data/images/TEST_NB/"
#define RGB_BASE_PATH "data/images/TEST_RGB/"

/* pixel const values */
#define PIXEL_MAX_SIZE 255
#define GRAY_LEVEL 64 

/* idx Image_s struct */
#define WIDTH_IDX 0
#define HEIGHT_IDX 1
#define CHANNELS_IDX 2

/* const values for quantification */
#define MASK_QUANT 0xC0
#define NB_BITS_SHIFTED 2

/* image dimension informations */
#define NB_SIZES 3

/* const values for file */
#define TEXT_EXTENSION ".txt"

/* structure that contains all informations about the image (file path, 
pointer on file descriptor, dimensions)*/
typedef struct
{
    /* the adress of the first char of the file path*/
    char* p_path;

    /* the adress of the file descriptor */
    FILE* p_image_txt;

    /* array that contains respectively width, height and channels */
    int a_sizes[NB_SIZES];
} Image_s;

Bool_e get_parameters_image(Image_s* p_image);
Bool_e quantify_image(Image_s* p_image, unsigned char a_quantified_image[]);
Bool_e index_image(char* p_path, Image_descriptor_s* p_descriptor);
void do_histogram_image(Image_s* p_image, unsigned char a_quantified_image[], unsigned char a_histogram[]);
Bool_e save_descriptor_image(FILE* p_base_descriptor_image, Image_descriptor_s* p_descriptor);
Bool_e automatic_image_indexation();

#endif