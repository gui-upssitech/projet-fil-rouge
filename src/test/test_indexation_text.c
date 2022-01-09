#include <stdio.h>
#include <stdlib.h>

#include "../../inc/indexation_text.h"
#include "../../inc/indexation_generic.h"

int main() 
{

    // == Steps to index text ==
    // 1. Get list of files
    // 2. Generate descriptor for each file
    // 3. Save descriptors to stack
    // 4. Save stack to file
    //system("foo.sh");

    if(automatic_indexing_by_data(LIST_BASE_TEXT_PATH, TEXT_BASE_PATH, BASE_TEXT_DESCRIPTOR_PATH, TEXT) == FALSE)
    {
        printf("Failed automatic text indexation.\n\r");
    }

    return 0;
}