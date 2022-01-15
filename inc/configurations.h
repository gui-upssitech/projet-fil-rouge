/*
Authors:    Constant ROUX,
            Julian TRANI,
            Peter PIRIOU--DEZY,
            Guillaume ROUSSIN,
            Nelson SANCHEZ
            
Date:       29/11/2021
*/

#ifndef CONFIGURATIONS_H
#define CONFIGURATIONS_H

#include <errno.h>
#include <string.h>

#include "toolbox.h"

#define CONFIG_FILE_PATH "admin/parameters.conf"

#define LIMIT_MODE "limite"
#define THRESHOLD_MODE "seuil"
typedef struct
{
    unsigned int indexing_text_filter_mode;
    unsigned int indexing_text_filter_value;
    unsigned int indexing_text_debug;
} Text_indexing_parameters_s;

#define MIN_QUANTIFICATION_SIZE 1
#define MAX_QUANTIFICATION_SIZE 5
typedef struct
{
    unsigned int quantification_size;
} Image_indexing_parameters_s;

#define MIN_LEVELS_SIZE 3
#define MAX_LEVELS_SIZE 1000
typedef struct
{
    unsigned int samples;
    unsigned int levels;
} Audio_indexing_parameters_s;

typedef struct
{
    double threshold;
} Image_comparison_parameters_s;

typedef struct
{
    double threshold;
    unsigned int step;
} Audio_comparison_parameters_s;

typedef struct
{
    Text_indexing_parameters_s text_indexing_parameters;
    Image_indexing_parameters_s image_indexing_parameters;
    Audio_indexing_parameters_s audio_indexing_parameters;
    Image_comparison_parameters_s image_comparison_parameters;
    Audio_comparison_parameters_s audio_comparison_parameters;
} Parameters_s;

extern Parameters_s G_parameters;

/**
 * @brief Load the configuration file in Parameters_s struct.
 * 
 * @return Bool_e TRUE if loading success, FALSE else.
 */
Bool_e load_configurations(void);

/**
 * @brief Load a configuration section.
 * 
 * @param config The configuration section to load.
 * @param value The value to set in the section.
 */
void load_configuration(char *config, char *value);

/**
 * @brief Save a new configuration in the ocnfiguration file.
 * 
 * @param config The config section to change the value.
 * @param value The new value for the config.
 * @return Bool_e TRUE if saving success, FALSE else.
 */
Bool_e save_configuration(char *config, char *value);

#endif