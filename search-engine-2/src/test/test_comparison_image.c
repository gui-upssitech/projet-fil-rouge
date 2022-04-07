#include <stdio.h>
#include <stdlib.h>

#include "comparaison_image.h"
#include "binary_search_tree.h"

int main(void)
{
    /* statements */
    Binary_search_tree_p tree;

    /* initializations */

    /* instructions */
    if(compare_image_files("/home/rxc3445a/Documents/projet-fil-rouge/data/images/TEST_RGB/02.txt", &tree, TRUE) == FALSE)
    {
        fprintf(stderr, "Error comparing image file.\n\r");
    }

    display_binary_search_tree(tree, IMAGE);

    return EXIT_SUCCESS;
}