#include <stdio.h>
#include <stdlib.h>

#include "../inc/indexation_image.h"
#include "../inc/toolbox.h"
#include "../inc/descriptor.h"

int main(void)  
{
    /* statements */
    Bool_e ret_value;
    Image_descriptor_s image_descriptor;

    /* initializations */

    /* instructions */
    ret_value = index_image("/home/rxc3445a/Documents/PFR/data/images/TEST_RGB/01.txt", &image_descriptor);
    if(ret_value == TRUE)
    {
        printf("Descriptor successfuly created.\n\r");
    }
    else
    {
        printf("Fail creating file descriptor.\n\r");
    }
    
    return EXIT_SUCCESS;
}