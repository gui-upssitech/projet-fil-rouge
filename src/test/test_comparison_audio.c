#include <stdio.h>
#include <stdlib.h>

#include "../../inc/comparaison_audio.h"

int main(void)
{
    /* statements */
    char *file1 = "corpus_fi.bin", *file2 = "jingle_fi.bin";
    
    /* initializations */
    /* instructions */
    
    compare_audio_files(file1, file2);

    return EXIT_SUCCESS;
}