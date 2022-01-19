/*
Authors:    Constant ROUX,
            Julian TRANI,
            Peter PIRIOU--DEZY,
            Guillaume ROUSSIN
                        
Date:       29/11/2021
*/

#ifndef INDEXATION_GENERIC_H
#define INDEXATION_GENERIC_H

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <dirent.h>

#include "toolbox.h"
#include "indexation_text.h"
#include "indexation_image.h"
#include "indexation_audio.h"
#include "dynamic_stack.h"


/**
 * @brief Index all files of the same data type.
 * 
 * @param p_list_base_path The file path of list base path.
 * @param p_data_path The file path of data.
 * @param p_base_path The file path of data base.
 * @param descriptor_type The type of data.
 * @return Bool_e TRUE if automatic indexing succeed, FALSE else.
 */
Bool_e automatic_indexing_by_data(char* p_list_base_path, char* p_data_path, char* p_base_path, Descriptor_e descriptor_type);

/**
 * @brief Index automatically all datas.
 * 
 * @return Bool_e TRUE if succeed, FALSE else.
 */
Bool_e automatic_indexing(void);

#endif