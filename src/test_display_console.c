#include <stdio.h>
#include <stdlib.h>

#include "../inc/display.h"
#include "../inc/toolbox.h"

int main(void)
{
    /* statements */
    unsigned int longueur;

    /* initializations */

    /* instructions */
    longueur = get_array_size_from_pointer("bonjour");
    printf("longueur texte attendu : 7 lettres\n\rlongueur texte obtenu : %d lettres\n\r\n\r", longueur);
    print_plate_console();
    display_text_console("");
    display_text_console("Moteur de Recherche");
    display_text_console("Chapelier  fou");
    display_text_console("impaire");
    display_text_console("");
    print_plate_console();


    return EXIT_SUCCESS;
}
