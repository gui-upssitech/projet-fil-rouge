/*
Authors:    Constant ROUX,
            Julian TRANI,
            Peter PIRIOU--DEZY,
            Guillaume ROUSSIN,
            Nelson SANCHEZ
            
Date:       29/11/2021
*/

#ifndef COMPARAISON_IMAGE_H
#define COMPARAISON_IMAGE_H

#include <stdlib.h>
#include <stdio.h>

#include "binary_search_tree.h"
#include "indexation_image.h"

Bool_e compare_image_descriptors(Image_descriptor_s p_descriptor1, Image_descriptor_s p_descriptor2, double* confidence);

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

void display_image_research_result(char* file, int* confidence);

#endif