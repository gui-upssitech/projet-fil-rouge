#ifndef CONFIGURATIONS_H
#define CONFIGURATIONS_H

typedef struct
{
    unsigned int samples;
    unsigned int levels;
} Audio_indexing_parameters_s;

typedef struct
{
    Audio_indexing_parameters_s audio_indexing_parameters;
} Parameters_s;

extern Parameters_s G_parameters;


#endif