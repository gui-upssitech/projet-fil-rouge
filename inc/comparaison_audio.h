/*
Authors:    Constant ROUX,
            Julian TRANI,
            Peter PIRIOU--DEZY,
            Guillaume ROUSSIN
                   
Date:       29/11/2021
*/

#ifndef COMPARAISON_AUDIO_H
#define COMPARAISON_AUDIO_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "binary_search_tree.h"
#include "toolbox.h"
#include "comparaison_generic.h"
#include "indexation_audio.h"
#include "configurations.h"

/**
 * @brief Compare two audio descriptors.
 * 
 * @param file_name The file name choose by the user for the search.
 * @param p_descriptor1 A pointer to the descriptor of file_name.
 * @param p_descriptor2 A pointer to the descriptor of a file in the database.
 * @param p_tree A pointer to the tree results.
 * @return Bool_e TRUE if comparison succeed, FALSE else.
 */
Bool_e compare_audio_descriptors(char* file_name, Audio_descriptor_s p_descriptor1, Audio_descriptor_s p_descriptor2, Binary_search_tree_p* p_tree);

/**
 * @brief Read an audio histogram in a descriptor file.
 * 
 * @param p_file An opened file descriptor with cursor at the histogram position.
 * @param p_descriptor A pointer to the audio descriptor in result.
 * @return Bool_e TRUE if read succeed, FALSE else.
 */
Bool_e read_histogram_audio(FILE* p_file, Audio_descriptor_s* p_descriptor);

/**
 * @brief Compare an audio file with all audios in the database.
 * 
 * @param request_file_path The request file path given by the user.
 * @param p_forest A pointer (which represents an array) on pointer of pointers of trees.
 * @param size The size of p_forest.
 * @return Bool_e TRUE if all comparisons succeed, FALSE else.
 */
Bool_e compare_audio_files(char* request_file_path, Binary_search_tree_p** p_forest, unsigned int* size);

#endif