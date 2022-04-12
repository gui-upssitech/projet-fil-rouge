#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "comparaison_audio.h"

int main(void)
{
    /* statements */
    Binary_search_tree_p* p_forest;
    unsigned int size;
    double time_spent;
    
    /* initializations */
    
    time_spent = 0.0;

    /* instructions */
    load_configurations();

    clock_t begin = clock();
    if(compare_audio_files("/home/rxc3445a/Documents/projet-fil-rouge/data/audios/TEST_SON/jingle_m6.bin", &p_forest, &size) == FALSE)
    {
        fprintf(stderr, "Error test comparing audio files.\n");
    }
    clock_t end = clock();

    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;

    printf("The elapsed time is %f seconds\n", time_spent);

    display_binary_search_tree(*(p_forest + 0), AUDIO);
    display_binary_search_tree(*(p_forest + 1), AUDIO);
    display_binary_search_tree(*(p_forest + 2), AUDIO);
    display_binary_search_tree(*(p_forest + 3), AUDIO);
    return EXIT_SUCCESS;
}