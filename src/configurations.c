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

#include "configurations.h"

Parameters_s G_parameters = {{0, 10, 0}, {2}, {1024, 100}, {60.0}, {1, 80.0}};

void load_configuration(char *config, char *value)
{
    value[0] = '0';
    if (strcmp(config, "indexing_text_filter_mode") == 0)
    {
        G_parameters.text_indexing_parameters.indexing_text_filter_mode = atoi(value);
    }
    if (strcmp(config, "indexing_text_filter_value") == 0)
    {
        G_parameters.text_indexing_parameters.indexing_text_filter_value = atoi(value);
    }
    if (strcmp(config, "indexing_text_debug") == 0)
    {
        G_parameters.text_indexing_parameters.indexing_text_debug = atoi(value);
    }
    if (strcmp(config, "indexing_text_number_table_index") == 0)
    {
        G_parameters.text_indexing_parameters.indexing_text_number_table_index = atoi(value);
    }

    if (strcmp(config, "indexing_image_quantification") == 0)
    {
        G_parameters.image_indexing_parameters.quantification_size = atoi(value);
    }

    if (strcmp(config, "indexing_audio_samples") == 0)
    {
        G_parameters.audio_indexing_parameters.samples = atoi(value);
    }
    if (strcmp(config, "indexing_audio_interval") == 0)
    {
        G_parameters.audio_indexing_parameters.levels = atoi(value);
    }

    if (strcmp(config, "comparison_image_threshold") == 0)
    {
        G_parameters.image_comparison_parameters.threshold = atof(value);
    }

    if (strcmp(config, "comparison_audio_step") == 0)
    {
        G_parameters.audio_comparison_parameters.step = atoi(value);
    }
    if (strcmp(config, "comparison_audio_threshold") == 0)
    {
        G_parameters.audio_comparison_parameters.threshold = atof(value);
    }
}

Bool_e load_configurations(void)
{
    /* statements */
    FILE *p_config_file;
    char buf[MAX_MEMORY_STRING], name[MAX_MEMORY_STRING], value[MAX_MEMORY_STRING];

    /* initializations */

    /* instructions */
    p_config_file = fopen(CONFIG_FILE_PATH, "r");
    if (p_config_file == NULL)
    {
        fprintf(stderr, "Error %d opening %s.\n\r", errno, CONFIG_FILE_PATH);
        return FALSE;
    }

    while (!feof(p_config_file))
    {
        fgets(buf, MAX_MEMORY_STRING, p_config_file);
        if (buf[0] != '#' && buf[0] != '\n')
        {
            sscanf(buf, "%[^=]%[^\n]", name, value);
            load_configuration(name, value);
        }
    }

    if (fclose(p_config_file) == EOF)
    {
        fprintf(stderr, "Error %d closing the file %s.\n\r", errno, CONFIG_FILE_PATH);
        return FALSE;
    }
    return TRUE;
}

Bool_e save_configuration(char *config, char *value)
{
    /* statements */
    FILE *p_sed;
    char cmd[MAX_MEMORY_STRING];

    /* instructions */
    sprintf(cmd, "sed -i 's/%s.*/%s=%s/' %s", config, config, value, CONFIG_FILE_PATH);
    p_sed = popen(cmd, "r");

    if (p_sed == NULL)
    {
        fprintf(stderr, "Error %d opening sed command.\n\r", errno);
        return FALSE;
    }

    if (pclose(p_sed) == EOF)
    {
        fprintf(stderr, "Error %d closing the sed command.\n\r", errno);
        return FALSE;
    }

    if (load_configurations() == FALSE)
    {
        fprintf(stderr, "Error loading configurations.\n\r");
    }

    return TRUE;
}