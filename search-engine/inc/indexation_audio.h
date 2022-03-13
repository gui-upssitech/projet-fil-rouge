/*
Authors:    Constant ROUX,
            Julian TRANI,
            Peter PIRIOU--DEZY,
            Guillaume ROUSSIN           
            
Date:       29/11/2021
*/

#ifndef INDEXATION_AUDIO_H
#define INDEXATION_AUDIO_H

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "toolbox.h"
#include "configurations.h"

/* descriptor file path constants */
#define LIST_BASE_AUDIO_PATH "descriptors/audio/list_base_audio.txt"
#define BASE_AUDIO_DESCRIPTOR_PATH "descriptors/audio/base_audio_descriptor.txt"

/* data file path constants */
#define SOUND_BASE_PATH "data/audio/"

/**
 * @brief structure that contains all informations about the image (file path, 
 * pointer on file descriptor, dimensions)
 * 
 */
typedef struct
{
    char* p_path; /**< the adress of the first char of the file path*/
    FILE* p_audio_bin; /**< the adress of the file descriptor */
    unsigned int size_doubles; /**< the number of 8 bytes packets (sizeof double) */

} Audio_s;

/**
 * @brief structure that contains all necessary informations to build the 
 * audio descriptor (...)
 * 
 */
typedef struct
{
    unsigned long id; /**< unique id of the descriptor based on the hashed file name */
    unsigned int* p_histogram; /**< histograms of the file */
    unsigned int samples; /**< the audio parameter samples */
    unsigned int levels; /**< the audio parameter levels */
    unsigned int i_windows; /**< the nummber of windows */

} Audio_descriptor_s;

/**
 * @brief Get the parameters of audio file.
 * 
 * @param p_audio The pointer of audio struct containing informations about the audio file.
 * @param p_descriptor A pointer of audio descriptor as result with new informations.
 */
void get_parameters_audio(Audio_s* p_audio, Audio_descriptor_s* p_descriptor);

/**
 * @brief Index audio file.
 * 
 * @param p_path The audio file path.
 * @param p_descriptor The audio descriptor as result.
 * @return Bool_e TRUE if index succeed, FALSE else.
 */
Bool_e index_audio(char* p_path, Audio_descriptor_s* p_descriptor);

/**
 * @brief Create the multiple necessary descriptors of audio file.
 * 
 * @param p_audio A pointer to the audio file informations.
 * @param p_descriptor A pointer to the audio descriptor.
 * @return Bool_e TRUE if creation of histograms succeed, FALSE else.
 */
Bool_e do_histograms_audio(Audio_s* p_audio, Audio_descriptor_s* p_descriptor);

/**
 * @brief Create an audio histogram.
 * 
 * @param p_audio A pointer to the audio file informations.
 * @param p_descriptor A pointer to the audio descriptor.
 * @param start_index The number of levels parameter.
 * @return Bool_e TRUE if creation of historam succed, FALSE else.
 */
Bool_e do_histogram_audio(Audio_s* p_audio, Audio_descriptor_s* p_descriptor, unsigned int start_index);

/**
 * @brief Save the audio descriptor.
 * 
 * @param p_base_descriptor_audio The file descriptor in which to save the descriptor.
 * @param p_descriptor The audio descriptor to save.
 * @return Bool_e TRUE if saving audio descriptor succeed, FALSE else.
 */
Bool_e save_descriptor_audio(FILE* p_base_descriptor_audio, Audio_descriptor_s* p_descriptor);

#endif