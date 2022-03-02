/*
Authors:    Constant ROUX,
            Julian TRANI,
            Peter PIRIOU--DEZY,
            Guillaume ROUSSIN            
            
Date:       29/11/2021
*/

#ifndef INDEXATION_IMAGE_H
#define INDEXATION_IMAGE_H

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <dirent.h>

#include "configurations.h"
#include "toolbox.h"

/* descriptor file path constants */
#define COLORS_BASE_PATH "admin/colors.conf"
#define LIST_BASE_IMAGE_PATH "descriptors/image/list_base_image.txt"
#define BASE_IMAGE_DESCRIPTOR_PATH "descriptors/image/base_image_descriptor.txt"

/* data file path constants */
#define NB_BASE_PATH "data/image/NB/"
#define RGB_BASE_PATH "data/image/RGB/"

/* pixel const values */
#define PIXEL_MAX_SIZE 255 

/* image data */
#define NB_SIZES 3
#define WIDTH_IDX 0
#define HEIGHT_IDX 1
#define CHANNELS_IDX 2
#define RGB_CHANNEL_SIZE 3
#define NB_CHANNEL_SIZE 1

/* const value for quantification */
#define CHAR_SIZE_BIT 8

/**
 * @brief structure that contains all informations about the image (file path, 
 * pointer on file descriptor, dimensions)
 * 
 */
typedef struct
{
    char* p_path; /**< the adress of the first char of the file path */
    FILE* p_image_txt; /**< the adress of the file descriptor */
    unsigned int a_sizes[NB_SIZES]; /**< array that contains respectively width, height and channels */

} Image_s;

/**
 * @brief structure that contains all necessary informations to build the 
 * image descriptor (id and histogram)
 * 
 */
typedef struct
{
    unsigned long id; /**< unique id of the descriptor based on the hashed file name */
    unsigned int* p_histogram; /**< histogram of the file */

} Image_descriptor_s;

/**
 * @brief Get the parameters of an image.
 * 
 * @param p_image A pointer of image informations struct.
 * @return Bool_e TRUE if parameters have been saved, FALSE else.
 */
Bool_e get_parameters_image(Image_s* p_image);

/**
 * @brief Quantify an image.
 * 
 * @param p_image A pointer to the image informations struct.
 * @param p_quantified_image A pointer representing an array of the quantified image.
 * @return Bool_e TRUE if quantification succeed, FALSE else.
 */
Bool_e quantify_image(Image_s* p_image, unsigned short* p_quantified_image);

/**
 * @brief Index an image.
 * 
 * @param p_path The path to the image to index.
 * @param p_descriptor The image descriptor as result.
 * @return Bool_e TRUE if indexing succeed, FALSE else.
 */
Bool_e index_image(char* p_path, Image_descriptor_s* p_descriptor);

/**
 * @brief Do the histogram of an image.
 * 
 * @param p_image A pointer to the image informations struct.
 * @param p_descriptor A pointer to the image descriptor as result.
 * @param p_quantified_image The image quantification array.
 * @return Bool_e TRUE if histogram creation succeed, FALSE else. 
 */
Bool_e do_histogram_image(Image_s* p_image, Image_descriptor_s* p_descriptor, unsigned short* p_quantified_image);

/**
 * @brief Save the image descriptor.
 * 
 * @param p_base_descriptor_image The file descriptor in which to save the descriptor.
 * @param p_descriptor The image descriptor to save.
 * @return Bool_e TRUE if saving image descriptor succeed, FALSE else.
 */
Bool_e save_descriptor_image(FILE* p_base_descriptor_image, Image_descriptor_s* p_descriptor);

#endif