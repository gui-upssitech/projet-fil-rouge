/*
Authors:    Constant ROUX,
            Julian TRANI,
            Peter PIRIOU--DEZY,
            Guillaume ROUSSIN,
            Nelson SANCHEZ
            
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
#define SOUND_BASE_PATH "data/audios/TEST_SON/"

/* structure that contains all informations about the image (file path, 
pointer on file descriptor, dimensions)*/
typedef struct
{
    /* the adress of the first char of the file path*/
    char* p_path;

    /* the adress of the file descriptor */
    FILE* p_audio_bin;

    /* the number of 8 bytes packets (sizeof double) */
    unsigned int size_doubles;

} Audio_s;

/* structure that contains all necessary informations to build the 
audio descriptor (...) */
typedef struct
{
    /* unique id of the descriptor based on the hashed file name */
    unsigned long id;

    /* histograms of the file */
    unsigned int* p_histogram;

    /* the audio parameters used to create the descriptor */
    unsigned int samples;
    unsigned int levels;

    /* the nummber of windows */
    unsigned int i_windows;

} Audio_descriptor_s;

void get_parameters_audio(Audio_s* p_audio, Audio_descriptor_s* p_descriptor);
Bool_e index_audio(char* p_path, Audio_descriptor_s* p_descriptor);
Bool_e do_histograms_audio(Audio_s* p_audio, Audio_descriptor_s* p_descriptor);
Bool_e do_histogram_audio(Audio_s* p_audio, Audio_descriptor_s* p_descriptor, unsigned int start_index);
Bool_e save_descriptor_audio(FILE* p_base_descriptor_audio, Audio_descriptor_s* p_descriptor);

#endif