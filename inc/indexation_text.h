/*
Authors:    Constant ROUX,
            Julian TRANI,
            Peter PIRIOU--DEZY,
            Guillaume ROUSSIN           
            
Date:       29/11/2021
*/

#include "toolbox.h"
#include "binary_tree_text.h"

#ifndef INDEXATION_TEXT_H
#define INDEXATION_TEXT_H

/* descriptor file path constants */
#define LIST_BASE_TEXT_PATH "descriptors/text/list_base_text.txt"
#define BASE_TEXT_DESCRIPTOR_PATH "descriptors/text/base_text_descriptor.txt"
#define INDEX_TABLE_TEXT_DESCRIPTOR_PATH "descriptors/text/index_table.txt"

/* data file path constants */
#define TEXT_BASE_PATH "data/texts/"

/* constants for bash script execution */
#define NB_ARGS 6

// TODO PASS TO CONFIG
#define TEXT_DESCRIPTOR_DEBUG_OUT           "results/debug/"
#define MAX_COMMAND_LENGTH 200


/* structure that contains all necessary informations to build the 
text descriptor (...) */
typedef struct
{
    /* unique id of the descriptor based on the hashed file name */
    unsigned long id;
    char* descriptor_contents;

} Text_descriptor_s;


/**
 * @brief Constructs the bash command to be executed for text treatement
 * 
 * @param input_path Path to the file to be indexed
 * @param desc_id Unique identifier associated with the file
 * @param output String containing the command to be run needs iniatialising outside of function
 * @return Bool_e will be FALSE if there is an error
 */
Bool_e generate_command(char *input_path, unsigned long desc_id, char *output);

Bool_e index_text(char* p_path, Text_descriptor_s* p_descriptor);
Bool_e save_descriptor_text(FILE* p_base_descriptor_text, Text_descriptor_s* p_descriptor);
Bool_e update_dictionary(Word_Tree_s* p_dictionary, Text_descriptor_s descriptor);


#endif