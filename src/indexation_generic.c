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

#include "../inc/dynamic_stack.h"
#include "../inc/indexation_generic.h"
#include "../inc/indexation_text.h"
#include "../inc/indexation_image.h"
#include "../inc/indexation_audio.h"

Bool_e automatic_generic_indexation(char* p_list_base_path, char* p_data_path, char* p_base_path, Descriptor_e descriptor_type)
{
    /* files statements */
    FILE* p_list_base;
    FILE* p_base;

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
            if(strstr(p_dir->d_name, (descriptor_type == TEXT ? XML_EXTENSION : (descriptor_type == AUDIO ? BIN_EXTENSION : TEXT_EXTENSION))) != NULL)
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
                            /* step 4 : add the new file in the list base */
                            if(fprintf(p_list_base, "%s %lu\n", p_dir->d_name, unit.image_descriptor.id) == EOF)
                            {
                                fprintf(stderr, "Error %d printing path and id in list base descriptor file.\n\r", errno);
                                return FALSE;
                            }
                        }
                        break;

                    case AUDIO:
                        if(index_audio(str_concat(p_data_path, p_dir->d_name), &(unit.audio_descriptor)) == FALSE)
                        {
                            fprintf(stderr, "Error creating file descriptor.\n\r");
                            return FALSE;
                        }
                        else
                        {
                            /* step 4 : add the new file in the list base */
                            if(fprintf(p_list_base, "%s %lu\n", p_dir->d_name, unit.audio_descriptor.id) == EOF)
                            {
                                fprintf(stderr, "Error %d printing path and id in list base descriptor file.\n\r", errno);
                                return FALSE;
                            }
                        }
                        break;
                    
                    default:
                        break;
                    }

                    /* step 5 : add the new descriptor in the stack */
                    p_dynamic_stack = add_unit_dynamic_stack(p_dynamic_stack, unit, descriptor_type);  
                }
            }
        }
        closedir(p_d);

        p_base = fopen(p_base_path, "a");
        if(p_base == NULL)
        {
            fprintf(stderr, "Error %d opening %s.\n\r", errno, p_base_path);
            return FALSE;
        }

        while(is_empty_dynamic_stack(p_dynamic_stack) == FALSE)
        {
            p_dynamic_stack = remove_unit_dynamic_stack(p_dynamic_stack, &unit, descriptor_type);
            switch(descriptor_type)
            {
                case TEXT:
                    break;

                case IMAGE:
                    if(save_descriptor_image(p_base, &(unit.image_descriptor)) == FALSE)
                    {
                        fprintf(stderr, "Error writing descriptor_id: %lu in %s", unit.image_descriptor.id, p_base_path);
                        return FALSE;
                    }
                    break;

                case AUDIO:
                    if(save_descriptor_audio(p_base, &(unit.audio_descriptor)) == FALSE)
                    {
                        fprintf(stderr, "Error writing descriptor_id: %lu in %s", unit.image_descriptor.id, p_base_path);
                        return FALSE;
                    }
                    break;
                    
                default:
                    break;
            }
        }

        if(fclose(p_base) == EOF)
        {
            fprintf(stderr, "Error %d closing the file %s.\n\r", errno, p_base_path);
            return FALSE;
        }
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