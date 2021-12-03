/*
Authors:    Constant ROUX,
            Julian TRANI,
            Peter PIRIOU--DEZY,
            Guillaume ROUSSIN,
            Nelson SANCHEZ
            
Date:       29/11/2021
*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <dirent.h>

#include "../inc/indexation_image.h"
#include "../inc/dynamic_stack.h"
#include "../inc/indexation_generic.h"

Bool_e automatic_generic_indexation(char* p_list_base_path, char* p_data_path, char* p_base_path, Descriptor_e descriptor_type)
{
    /* files statements */
    FILE* p_list_base;

    /* dir explorer statements */
    struct dirent* p_dir;
    DIR* p_d;

    /* descriptors statements */
    Dynamic_stack_p p_dynamic_stack;
    Unit_u unit;

    /* initializations */
    p_dynamic_stack = init_dynamic_stack();
    p_list_base = fopen(p_list_base_path, "a+");

    /* instructions */
    if(p_list_base == NULL)
    {
        fprintf(stderr, "Error %d opening %s.\n\r", errno, p_list_base_path);
        return FALSE;
    }

    p_d = opendir(p_data_path);
    if(p_d)
    {
        while((p_dir = readdir(p_d)) != NULL)
        {
            /* step 1 : check if the read file contains the string extension file */
            if(strstr(p_dir->d_name, (descriptor_type == TEXT) ? XML_EXTENSION : TEXT_EXTENSION) != NULL)
            {
                /* step 2 : check if the index table contains the file being processed */
                if(file_contains_substring(p_list_base, p_dir->d_name) == FALSE)
                {
                    /* step 3 : create the descriptor of the file */
                    switch(descriptor_type)
                    {
                    case TEXT:
                        break;
                    
                    case IMAGE:
                        if(index_image(str_concat(p_data_path, p_dir->d_name), &(unit.image_descriptor)) == FALSE)
                        {
                            fprintf(stderr, "Error creating file descriptor.\n\r");
                            return FALSE;
                        }
                        else
                        {
                            /* step 4 : add the new file in the index table */
                            fprintf(p_list_base, "%s %lu\n", p_dir->d_name, unit.image_descriptor.id);
                        }
                        break;

                    case AUDIO:
                        break;
                    
                    default:
                        break;
                    }

                    /* step 5 : add the new descriptor in the stack */
                    p_dynamic_stack = add_unit_dynamic_stack(p_dynamic_stack, unit);  
                }
            }
        }
        closedir(p_d);

        // TO DO : save descriptor
    }
    else
    {
        fprintf(stderr, "Error %d opening %s.\n\r", errno, p_list_base_path);
        return FALSE;
    }

    if(fclose(p_list_base) == EOF)
    {
        fprintf(stderr, "Error %d closing the file %s.\n\r", errno, p_list_base_path);
        return FALSE;
    }
    return TRUE;
}