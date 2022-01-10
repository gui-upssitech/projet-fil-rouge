/*
Authors:    Constant ROUX,
            Julian TRANI,
            Peter PIRIOU--DEZY,
            Guillaume ROUSSIN,
            Nelson SANCHEZ
            
Date:       29/11/2021
*/

#ifndef COMPARAISON_AUDIO_H
#define COMPARAISON_AUDIO_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "binary_search_tree.h"
#include "toolbox.h"
#include "comparaison_generic.h"
#include "indexation_audio.h"
#include "configurations.h"

Bool_e compare_audio_descriptors(char* file_name, Audio_descriptor_s p_descriptor1, Audio_descriptor_s p_descriptor2, Binary_search_tree_p* p_tree);
Bool_e read_histogram_audio(FILE* p_file, Audio_descriptor_s* p_descriptor);
Bool_e compare_audio_files(char* request_file_path, Binary_search_tree_p** p_forest, unsigned int* size);

#endif