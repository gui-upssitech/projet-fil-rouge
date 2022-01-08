/*
Authors:    Constant ROUX,
            Julian TRANI,
            Peter PIRIOU--DEZY,
            Guillaume ROUSSIN,
            Nelson SANCHEZ
            
Date:       29/11/2021
*/

#include "indexation_audio.h"

void get_parameters_audio(Audio_s* p_audio, Audio_descriptor_s* p_descriptor)
{
    p_descriptor->samples = G_parameters.audio_indexing_parameters.samples;
    p_descriptor->levels = G_parameters.audio_indexing_parameters.levels;
    p_audio->size_doubles = get_bytes_size_file(p_audio->p_audio_bin) / 8;
}

Bool_e save_descriptor_audio(FILE* p_base_descriptor_audio, Audio_descriptor_s* p_descriptor)
{
    /* statements */
    unsigned int i, j;

    /* instructions */
    if(fprintf(p_base_descriptor_audio, "%lu\n", p_descriptor->id) == EOF)
    {
        fprintf(stderr, "Error %d printing id of image descriptor.\n\r", errno);
        return FALSE;
    }

    if(fprintf(p_base_descriptor_audio, "%d\n", p_descriptor->i_windows) == EOF)
    {
        fprintf(stderr, "Error %d printing id of image descriptor.\n\r", errno);
        return FALSE;
    }

    for(i = 0; i < p_descriptor->i_windows; i++)
    {
        for(j = 0; j < p_descriptor->levels; j++)
        {
            if(fprintf(p_base_descriptor_audio, "%d ", *((p_descriptor->p_histogram) + i * (p_descriptor->levels) + j)) == EOF)
            {
                fprintf(stderr, "Error %d printing histogram value of image descriptor at %d:%d.\n\r", errno, i, j);
                return FALSE;
            }
        }

       if(fprintf(p_base_descriptor_audio, "\n") == EOF)
        {
            fprintf(stderr, "Error %d printing new line char in image descriptor.\n\r", errno);
            return FALSE;
        } 
    }

    if(fprintf(p_base_descriptor_audio, "\n") == EOF)
    {
        fprintf(stderr, "Error %d printing new line char in image descriptor.\n\r", errno);
        return FALSE;
    }
    return TRUE;
}

Bool_e do_histogram_audio(Audio_s* p_audio, Audio_descriptor_s* p_descriptor, unsigned int start_index)
{
    /* statements */
    unsigned int i;
    double value;
    char bytes[8];

    /* initializations */

    /* instructions */
    for(i = 0; (i < p_descriptor->samples) && !feof(p_audio->p_audio_bin); i++)
    {
        if(fread(bytes, 8, 1, p_audio->p_audio_bin) != 1 && !feof(p_audio->p_audio_bin))
        {
            fprintf(stderr, "Error reading binary file %s.\n\r", p_audio->p_path);
            return FALSE;
        }
        
        value = *((double*) bytes);
        *(p_descriptor->p_histogram + start_index + (unsigned int) (((p_descriptor->levels - 1) / 2.) * (value + 1.))) += 1;
    }
    return TRUE;
}

Bool_e do_histograms_audio(Audio_s* p_audio, Audio_descriptor_s* p_descriptor)
{
    /* statements */
    unsigned int i;

    /* initializations */
    p_descriptor->p_histogram = (unsigned int*) malloc((p_descriptor->levels * p_descriptor->i_windows) * sizeof(unsigned int));

    /* instructions */
    if(p_descriptor->p_histogram == NULL)
    {
        fprintf(stderr, "Error memory allocation.\n\r");
        return FALSE;
    }

    memset(p_descriptor->p_histogram, 0, (p_descriptor->levels * p_descriptor->i_windows) * sizeof(unsigned int));


    for(i = 0; i < p_descriptor->i_windows; i++)
    {
        if(do_histogram_audio(p_audio, p_descriptor, i * p_descriptor->levels) == FALSE)
        {
            fprintf(stderr, "Error creating histogram of %s at adress block : %p.\n\r", p_audio->p_path, i * p_descriptor->levels + p_audio->p_audio_bin);
            return FALSE;
        }
    }

    return TRUE;
}

Bool_e index_audio(char* p_path, Audio_descriptor_s* p_descriptor)
{
    /* statements */
    Audio_s audio;

    /* initializations */
    audio.p_audio_bin = fopen(p_path, "rb");

    /* instructions */
    if(audio.p_audio_bin == NULL)
    {
        fprintf(stderr, "Error %d opening %s.\n\r", errno, p_path);
        return FALSE;
    }
    else
    {
        /* step 1 : get audio/descriptor parameters */
        audio.p_path = p_path;
        get_parameters_audio(&audio, p_descriptor);
        p_descriptor->i_windows = ((audio.size_doubles) / (p_descriptor->samples));

        /* step 2 : generate id */
        p_descriptor->id = hash(p_path);

        /* step 3 : do histograms */
        do_histograms_audio(&audio, p_descriptor);
    }

    if(fclose(audio.p_audio_bin) == EOF)
    {
        fprintf(stderr, "Error %d closing the file %s.\n\r", errno, audio.p_path);
        return FALSE;
    }

    return TRUE;
}