/*
Authors:    Constant ROUX,
            Julian TRANI,
            Peter PIRIOU--DEZY,
            Guillaume ROUSSIN           
            
Date:       29/11/2021
*/

#ifndef COMPARAISON_IMAGE_H
#define COMPARAISON_IMAGE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "binary_search_tree.h"
#include "indexation_image.h"

/**
 * @brief Compre two image descriptors.
 * 
 * @param p_descriptor1 The first descriptor.
 * @param p_descriptor2 The second descriptor.
 * @param confidence The result of the comparison (a percentage between 0.0 % and 100.0 %)
 * @return Bool_e TRUE if comparison succeed, FALSE else.
 */
Bool_e compare_image_descriptors(Image_descriptor_s p_descriptor1, Image_descriptor_s p_descriptor2, double* confidence);

/**
 * @brief Read an image histogram in a descriptor file.
 * 
 * @param p_file The descriptor file with cursor at histogram position.
 * @param p_descriptor A pointer to the image descriptor in result.
 * @return Bool_e TRUE if read succeed, FALSE else.
 */
Bool_e read_histogram_image(FILE* p_file, Image_descriptor_s* p_descriptor);

/**
 * @brief Compare a request .txt file corresponding to an image (RGB or GRAY) with.
 * 
 * @param request_file_path The absolute path or relative path of the request file.
 * @param results A pointer of binary search tree containing the results of the search (image name with confidence greater than the threshold).
 * @param colored A boolean variable which that expects TRUE if the request image is RGB, FALSE if gray.
 * @return Bool_e TRUE if the image comparison succeed, FALSE else.
 */
Bool_e compare_image_files(char* request_file_path, Binary_search_tree_p* results, Bool_e colored);

/**
 * @brief Display image result of research menu.
 * 
 * @param file The found file name.
 * @param confidence The confidence of the comparison between file and the searched file by user.
 */
void display_image_research_result(char* file, int* confidence);

#endif