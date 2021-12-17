#include <stdio.h>
#include <stdlib.h>

#include "../../inc/toolbox.h"
#include "../../inc/indexation_generic.h"

int main() {

    //printf("Chemin de base du répertoire: %s\n", run_command("pwd"));
    //printf("Chemin du dossier data: %s\n", get_path("/data"));

    //printf("command output :\n%s\n", run_command("/bin/bash ../indexation_text/indexation_text.sh"));

    automatic_generic_indexation("descriptors/text/liste_base_audio.txt", "data/texts/", "descriptors/text/base_text_descriptor.txt", TEXT);

    // == Steps to index text ==
    // 1. Get list of files
    // 2. Generate descriptor for each file
    // 3. Save descriptors to stack
    // 4. Save stack to file

    return 0;
}