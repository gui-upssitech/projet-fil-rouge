#include <stdio.h>
#include <stdlib.h>

#include "comparaison_audio.h"

int main(void)
{
    /* statements */
    Binary_search_tree_p tree;
    
    /* initializations */
    /* instructions */
    
    compare_audio_files("/home/rxc3445a/Documents/projet-fil-rouge/data/audios/TEST_SON/jingle_fi.bin", &tree);
    display_binary_search_tree(tree, AUDIO);
    return EXIT_SUCCESS;
}