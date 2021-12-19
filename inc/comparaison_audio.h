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

#include "binary_search_tree.h"
#include "toolbox.h"
#include "comparaison_generic.h"
#include "indexation_audio.h"

Bool_e compare_audio_descriptors(Audio_descriptor_s p_descriptor1, Audio_descriptor_s p_descriptor2, int** time_codes);
Bool_e read_histogram_audio(FILE* p_file, Audio_descriptor_s* p_descriptor);
Bool_e compare_audio_files(char* file1, char* file2);
void display_audio_research_result(char* file, int* time_codes);

#endif