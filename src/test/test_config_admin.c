#include <stdlib.h>
#include <stdio.h>

#include "configurations.h"

int main(void)
{
    load_configurations();
    save_configuration("indexing_audio_samples", "1024");
    return EXIT_SUCCESS;
}