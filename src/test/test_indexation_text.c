#include <stdio.h>
#include <stdlib.h>

#include "../../inc/indexation_text.h"

int main() {

    // == Steps to index text ==
    // 1. Get list of files
    // 2. Generate descriptor for each file
    // 3. Save descriptors to stack
    // 4. Save stack to file
    //system("foo.sh");

    generate_descriptor("03-Des_chercheurs_parviennent_α_rΘgΘnΘrer.xml");

    return 0;
}