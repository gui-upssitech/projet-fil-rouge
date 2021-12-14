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

#include "toolbox.h"
#include "comparaison_generic.h"
#include "indexation_audio.h"

Bool_e compare_audio_files(char* file1, char* file2);

#endif