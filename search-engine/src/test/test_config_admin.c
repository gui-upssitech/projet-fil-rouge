#include <stdlib.h>
#include <stdio.h>

#include "configurations.h"

int main(void)
{
    load_configurations();
    save_configuration("indexing_audio_samples", "MAX_MEMORY_STRING");
    return EXIT_SUCCESS;
}