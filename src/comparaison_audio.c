/*
Authors:    Constant ROUX,
            Julian TRANI,
            Peter PIRIOU--DEZY,
            Guillaume ROUSSIN,
            Nelson SANCHEZ
            
Date:       29/11/2021
*/

#include "../inc/comparaison_audio.h"

Bool_e compare_audio_descriptors(Audio_descriptor_s p_descriptor1, Audio_descriptor_s p_descriptor2, int** time_codes)
{
    /* statements */
    int shift_value, i, j;
    double double_buffer;
    Audio_descriptor_s buffer;
    int size_time_codes;

    /* initializations */
    size_time_codes = -1;
    *time_codes = (int*) malloc(sizeof(int));

    /* instructions */
    if(time_codes == NULL)
    {
        fprintf(stderr, "Error memory allocation.\n\r");
        return FALSE;
    }

    if(p_descriptor2.i_windows > p_descriptor1.i_windows)
    {
        buffer = p_descriptor1;
        p_descriptor1 = p_descriptor2;
        p_descriptor2 = buffer;
    }

    shift_value = p_descriptor1.i_windows - p_descriptor2.i_windows + 1;

    for(i = 0; i < shift_value; i++)
    {
        double confidence_sum = 0;

        for(j = 0; j < p_descriptor2.i_windows; j++)
        {
            if(compare_histogram(  p_descriptor1.levels, 
                                &p_descriptor1.p_histogram[i * p_descriptor2.levels + j * p_descriptor2.levels], 
                                &p_descriptor2.p_histogram[j * p_descriptor2.levels], 
                                &double_buffer  ) == FALSE)
            {
                fprintf(stderr, "Error comparing descriptors.\n\r");
                return FALSE;
            }

            confidence_sum += double_buffer;
        }

        if(confidence_sum / p_descriptor2.i_windows > G_parameters.audio_comparison_parameters.threshold)
        {
            if(size_time_codes == -1)
            {
                size_time_codes++;
                (*time_codes)[size_time_codes] = i / 15; // TO DO fix magic constant
            }
            else if(i / 15 > ((*time_codes)[size_time_codes] + p_descriptor2.i_windows / 15))
            {
                size_time_codes++;
                *time_codes = (int*) realloc(*time_codes, sizeof(int) * (size_time_codes + 1));
                if(time_codes == NULL)
                {
                    fprintf(stderr, "Error memory reallocation.\n\r");
                    return FALSE;
                }
                (*time_codes)[size_time_codes] = i / 15;
            }
        }
    }
    /* end of array */
    size_time_codes++;
    *time_codes = (int*) realloc(*time_codes, sizeof(int) * (size_time_codes + 1));
    if(time_codes == NULL)
    {
        fprintf(stderr, "Error memory reallocation.\n\r");
        return FALSE;
    }
    (*time_codes)[size_time_codes] = -1;
    return TRUE;
}

Bool_e read_histogram_audio(FILE* p_file, Audio_descriptor_s* p_descriptor)
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

/* NOTE : first parameter is the user request */
Bool_e compare_audio_files(char* request_file_path, Binary_search_tree_p* results)
{
    /* command descriptor statements */
    FILE* p_cmd;
    char buf[256];

    /* image descriptor statements */
    unsigned int windows_order;
    unsigned long hash_file, hash_file_read;
    Audio_descriptor_s request_descriptor_file, descriptor_file;
    char* p_line;
    FILE* p_file;

    /* result statement */
    Result_s result;
    double confidence;
    
    /* other statements */
    unsigned int i;

    /* initializations */
    *results = init_binary_search_tree();

    /* declarations */
    /* step 1 : create descriptor of request file */
    if(index_audio(request_file_path, &request_descriptor_file) == FALSE)
    {
        fprintf(stderr, "Error indexing request file %s.\n\r", request_file_path);
        return FALSE;
    }

    /* step 2 : find database image files */
    p_cmd = popen(str_concat(str_concat("find ", SOUND_BASE_PATH), "*.txt -printf \"%f\n\""), "r");

    if(p_cmd == NULL)
    {
        fprintf(stderr, "Error %d opening find command.\n\r", errno);
        return FALSE;
    }

    /* step 3 : browse all the database files */
    while(fgets(buf, sizeof(buf), p_cmd) != 0)
    {
        /* step 3.1 : open the base image list */
        p_file = fopen(LIST_BASE_AUDIO_PATH, "r");
        if(p_file == NULL)
        {
            fprintf(stderr, "Error %d opening file %s.\n\r", errno, LIST_BASE_AUDIO_PATH);
            return FALSE;
        }

        /* step 3.2 : find the line containing the file name and the hash code */
        for(i = 0; buf[i] != '\0' && i < 256; i++){} buf[i - 1] = '\0'; 
        if(file_contains_substring(p_file, buf, &p_line) == FALSE)
        {
            fprintf(stderr, "Error impossible to find the file.\n\r");
            return FALSE;
        }

        /* step 3.3 : get the hash code of the file containing in the read line */
        if(sscanf(p_line, "%*[^ ] %lu", &hash_file) != 1)
        {
            fprintf(stderr, "Error reading hash code for file.\n\r");
        }

        /* step 3.4 : close the list base image file */
        if(fclose(p_file) == EOF)
        {
            fprintf(stderr, "Error %d closing the file %s.\n\r", errno, LIST_BASE_AUDIO_PATH);
            return FALSE;
        }

        /* step 3.5 : fill descriptor file */
        descriptor_file.id = hash_file;
        descriptor_file.levels = G_parameters.audio_indexing_parameters.levels;
        descriptor_file.samples = G_parameters.audio_indexing_parameters.samples;

        /* step 3.6 : open base image image descriptor */
        p_file = fopen(BASE_IMAGE_DESCRIPTOR_PATH, "r");
        if(p_file == NULL)
        {
            fprintf(stderr, "Error %d opening %s.\n\r", errno, BASE_IMAGE_DESCRIPTOR_PATH);
            return FALSE;
        }

        /* step 3.7 : find histogram of file */
        while(!feof(p_file))
        {
            hash_file_read = 0;
            if(fscanf(p_file, "%lu", &hash_file_read) == 1)
            {
                if(hash_file_read == hash_file)
                {
                    if(read_histogram_audio(p_file, &descriptor_file) == FALSE)
                    {
                        fprintf(stderr, "Error reading image histogram.\n\r");
                    }
                }
            }
        }

        if(fclose(p_file) == EOF)
        {
            fprintf(stderr, "Error %d closing the file %s.\n\r", errno, BASE_IMAGE_DESCRIPTOR_PATH);
            return FALSE;
        }

        /* step 3.8 : launch comparison */
        if(compare_audio_descriptors(request_descriptor_file, descriptor_file, &confidence) == FALSE)
        {
            fprintf(stderr, "Error comparing descriptor files.\n\r");
            return FALSE;
        } // TO DO

        if(confidence >= G_parameters.image_comparison_parameters.threshold)
        {
            for(i = 0; buf[i] != '\0' && i < 256; i++)
            {
                result.name[i] = buf[i];
            }
            
            result.confidence = confidence;
            result.time_code = -1;
            add_node_binary_search_tree(results, result);
        }
    }

    if(pclose(p_cmd) == EOF)
    {
        fprintf(stderr, "Error %d closing the find command.\n\r", errno);
        return FALSE;
    }

    return TRUE;
}