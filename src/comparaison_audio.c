/*
Authors:    Constant ROUX,
            Julian TRANI,
            Peter PIRIOU--DEZY,
            Guillaume ROUSSIN,
            Nelson SANCHEZ
            
Date:       29/11/2021
*/

#include "../inc/comparaison_audio.h"

Bool_e compare_audio_descriptors(Audio_descriptor_s p_descriptor1, Audio_descriptor_s p_descriptor2)
{
    return FALSE;
}

Bool_e read_histogram(FILE* p_file, Audio_descriptor_s* p_descriptor)
{
    /* statements */
    unsigned int i;
    unsigned int read_value;
    unsigned int size;

    /* instructions */
    if(fscanf(p_file, "%d", &size) != 1)
    {
        fprintf(stderr, "Error reading descriptor size.\n\r");
        return FALSE;
    }
    p_descriptor->i_windows = size;
    p_descriptor->p_histogram = (unsigned int*) malloc(size * G_parameters.audio_indexing_parameters.levels * sizeof(unsigned int));
    if(p_descriptor->p_histogram == NULL)
    {
        fprintf(stderr, "Error memory allocation.\n\r");
        return FALSE;
    }

    for(i = 0; i < size * G_parameters.audio_indexing_parameters.levels; i++)
    {
        if(fscanf(p_file, "%u", &read_value) != 1)
        {
                fprintf(stderr, "Error reading descriptor value.\n\r");
                return FALSE;
        }
        p_descriptor->p_histogram[i] = read_value;
    }
    return TRUE;
}

Bool_e compare_audio_files(char* file1, char* file2)
{
    /* statements */
    char* p_line;
    FILE* p_file;
    unsigned long hash_file1, hash_file2, hash_file_read;
    Audio_descriptor_s descriptor_file1, descriptor_file2;

    /* initializations */
    p_file = fopen(LIST_BASE_AUDIO_PATH, "r");

    /* declarations */
    /* step 1 : get hashed name */
    if(p_file == NULL)
    {
        fprintf(stderr, "Error %d opening %s.\n\r", errno, LIST_BASE_AUDIO_PATH);
        return FALSE;
    }

    if(file_contains_substring(p_file, file1, &p_line) == FALSE)
    {
        fprintf(stderr, "Error impossible to find the file 1.\n\r");
        return FALSE;
    }
    fseek(p_file, 0, SEEK_SET);

    if(sscanf(p_line, "%*[^ ] %lu", &hash_file1) != 1)
    {
        fprintf(stderr, "Error reading hash code for file %s.\n\r", file1);
    }
    
    if(file_contains_substring(p_file, file2, &p_line) == FALSE)
    {
        fprintf(stderr, "Error impossible to find the file 2.\n\r");
        return FALSE;
    }

    if(sscanf(p_line, "%*[^ ] %lu", &hash_file2) != 1)
    {
        fprintf(stderr, "Error reading hash code for file %s.\n\r", file2);
    }

    if(fclose(p_file) == EOF)
    {
        fprintf(stderr, "Error %d closing the file %s.\n\r", errno, LIST_BASE_AUDIO_PATH);
        return FALSE;
    }

    /* step 2 : find descriptor using hash code */
    /* step 2.1 : find basics of descriptor of file 1 */
    descriptor_file1.id = hash_file1;
    descriptor_file1.levels = G_parameters.audio_indexing_parameters.levels;
    descriptor_file1.samples = G_parameters.audio_indexing_parameters.samples;
    descriptor_file1.i_windows = 0;

    /* step 2.2 : find basics of descriptor of file 2 */
    descriptor_file2.id = hash_file2;
    descriptor_file2.levels = G_parameters.audio_indexing_parameters.levels;
    descriptor_file2.samples = G_parameters.audio_indexing_parameters.samples;
    descriptor_file2.i_windows = 0;

    p_file = fopen(BASE_AUDIO_DESCRIPTOR_PATH, "r");
    if(p_file == NULL)
    {
        fprintf(stderr, "Error %d opening %s.\n\r", errno, BASE_AUDIO_DESCRIPTOR_PATH);
        return FALSE;
    }

    while(!feof(p_file))
    {
        hash_file_read = 0;
        if(fscanf(p_file, "%lu", &hash_file_read) == 1)
        {
            /* step 2.3 : find hsitogram of descriptor of file 1 */
            if(hash_file_read == hash_file1)
            {
                if(read_histogram(p_file, &descriptor_file1) == FALSE)
                {
                    fprintf(stderr, "Error reading histogram of %s.\n\r", file1);
                }
            }

            /* step 2.4 : find hsitogram of descriptor of file 2 */
            if(hash_file_read == hash_file2)
            {
                if(read_histogram(p_file, &descriptor_file2) == FALSE)
                {
                    fprintf(stderr, "Error reading histogram of %s.\n\r", file2);
                }
            }

            if(descriptor_file1.i_windows != 0 && descriptor_file2.i_windows != 0)
            {
                break;
            }
        }
    }

    /* step 4 : launch comparison */

    /* step 5 : find time code */

    /* step 6 : display result */
    
    return TRUE;
}