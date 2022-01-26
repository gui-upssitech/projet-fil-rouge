/*
Authors:    Constant ROUX,
            Julian TRANI,
            Peter PIRIOU--DEZY,
            Guillaume ROUSSIN
            
            
Date:       29/11/2021
*/

#include "comparaison_image.h"


Bool_e compare_image_descriptors(Image_descriptor_s p_descriptor1, Image_descriptor_s p_descriptor2, double* confidence)
{
    /* instructions */
    compare_histogram(  PWRTWO(RGB_CHANNEL_SIZE * G_parameters.image_indexing_parameters.quantification_size), 
                        p_descriptor1.p_histogram, 
                        p_descriptor2.p_histogram, 
                        confidence   );
    
    return TRUE;
}

Bool_e read_histogram_image(FILE* p_file, Image_descriptor_s* p_descriptor)
{
    /* statements */
    unsigned int i;
    unsigned int read_value;

    /* instructions */
    p_descriptor->p_histogram = (unsigned int*) malloc(PWRTWO(RGB_CHANNEL_SIZE * G_parameters.image_indexing_parameters.quantification_size) * sizeof(unsigned int));
    if(p_descriptor->p_histogram == NULL)
    {
        fprintf(stderr, "Error memory allocation.\n\r");
        return FALSE;
    }

    for(i = 0; i < (unsigned int) PWRTWO(RGB_CHANNEL_SIZE * G_parameters.image_indexing_parameters.quantification_size); i++)
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
Bool_e compare_image_files(char* request_file_path, Binary_search_tree_p* results, Bool_e colored)
{
    /* command descriptor statements */
    FILE* p_cmd;
    char buf[MAX_MEMORY_STRING];
    char command[MAX_MEMORY_STRING];

    /* image descriptor statements */
    unsigned long hash_file, hash_file_read;
    Image_descriptor_s request_descriptor_file, descriptor_file;
    char* p_line;
    FILE* p_file;

    /* result statement */
    Result_s result;
    double confidence;
    
    /* other statements */
    unsigned int i;

    /* initializations */
    *results = init_binary_search_tree();

    /* statements */
    /* step 1 : create descriptor of request file */
    if(index_image(request_file_path, &request_descriptor_file) == FALSE)
    {
        fprintf(stderr, "Error indexing request file %s.\n\r", request_file_path);
        return FALSE;
    }

    /* step 2 : find database image files */
    if(colored == TRUE)
    {
        sprintf(command, "find %s*.txt -printf \"%%f\n\"", RGB_BASE_PATH);
        p_cmd = popen(command, "r");
    }
    else
    {
        sprintf(command, "find %s*.txt -printf \"%%f\n\"", NB_BASE_PATH);
        p_cmd = popen(command, "r");
    }

    if(p_cmd == NULL)
    {
        fprintf(stderr, "Error %d opening find command.\n\r", errno);
        return FALSE;
    }

    /* step 3 : browse all the database files */
    while(fgets(buf, sizeof(buf), p_cmd) != 0)
    {
        for(i = 0; buf[i] != '\0' && i < MAX_MEMORY_STRING; i++){} buf[i - 1] = '\0'; 
        if(strstr(request_file_path, buf) != NULL)
        {
            continue;
        }

        /* step 3.1 : open the base image list */
        p_file = fopen(LIST_BASE_IMAGE_PATH, "r");
        if(p_file == NULL)
        {
            fprintf(stderr, "Error %d opening file %s.\n\r", errno, LIST_BASE_IMAGE_PATH);
            return FALSE;
        }

        /* step 3.2 : find the line containing the file name and the hash code */
        if(file_contains_substring(p_file, buf, &p_line) == FALSE)
        {
            fprintf(stderr, "Error impossible to find the file.\n\r");
            return FALSE;
        }

        /* step 3.3 : get the hash code of the file containing in the read line */
        if(sscanf(p_line, "%*[^ ] %lu", &hash_file) != 1)
        {
            fprintf(stderr, "Error reading hash code for file.\n\r");
            return FALSE;
        }

        free(p_line);

        /* step 3.4 : close the list base image file */
        if(fclose(p_file) == EOF)
        {
            fprintf(stderr, "Error %d closing the file %s.\n\r", errno, LIST_BASE_AUDIO_PATH);
            return FALSE;
        }

        /* step 3.5 : fill descriptor file */
        descriptor_file.id = hash_file;

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
                    if(read_histogram_image(p_file, &descriptor_file) == FALSE)
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
        if(compare_image_descriptors(request_descriptor_file, descriptor_file, &confidence) == FALSE)
        {
            fprintf(stderr, "Error comparing descriptor files.\n\r");
            return FALSE;
        }

        free(descriptor_file.p_histogram);

        if(confidence >= G_parameters.image_comparison_parameters.threshold)
        {
            memset(result.name, 0, MAX_MEMORY_STRING);
            for(i = 0; buf[i] != '\0' && i < MAX_MEMORY_STRING; i++)
            {
                result.name[i] = buf[i];
            }

            if(colored == TRUE)
            {
                strcpy(strrchr(result.name, '.'), ".jpg");
            }
            else
            {
                strcpy(strrchr(result.name, '.'), ".bmp");
            }
            
            result.confidence = confidence;
            result.time_code = -1;
            add_node_binary_search_tree_image(results, result);
        }
    }

    free(request_descriptor_file.p_histogram);

    if(pclose(p_cmd) == EOF)
    {
        fprintf(stderr, "Error %d closing the find command.\n\r", errno);
        return FALSE;
    }

    return TRUE;
}