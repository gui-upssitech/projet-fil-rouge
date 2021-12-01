#include <stdio.h>
#include <stdlib.h>

#include "../inc/console.h"
#include "../inc/toolbox.h"

void clear_console()
{
    system("clear");
}

void print_plate_console()
{
    /* declarations */
    unsigned int i;

    /* instructions */
    printf("%s", CORNER);
    for(i = 0; i < MAX_CHAR_PER_LINE - 2; i++)
    {
        printf("%s", PLATE);
    }
    printf("%s\n\r", CORNER);
}

void print_blank_console(unsigned int blank_size)
{
    /* declarations */
    int i;

    /* instructions */
    for(i = 0; i < blank_size; i++)
    {
        printf("%s", SPACE);
    }
}

void display_centered_text_console(char* p_text)
{
    /* statements */
    unsigned int long size, blank_size;
    Bool_e even;

    /* initializations */
    even = TRUE;

    /* instructions */
    size = get_array_size_from_pointer(p_text);
    if(size > MAX_CHAR_PER_LINE - 2)
    {
        printf("Error overflow writing line menu.\n\r");
        return;
    }
    if((MAX_CHAR_PER_LINE - size - 2) % 2 == 1)
    {
        even = FALSE;
    }
    blank_size = (MAX_CHAR_PER_LINE - size - 2) / 2;
    printf("%s", WALL);
    print_blank_console(blank_size);
    printf("%s", p_text);
    print_blank_console(even == TRUE ? blank_size : blank_size + 1);
    printf("%s\n\r", WALL);
}

/* the 'q' choice is include in the num_choices variable */
char get_char_menu(char num_choices)
{
    /* initializations */
    char c;

    /* instructions */
    do
    {
        c = getch();
    } while ((c <= '0' || c >= num_choices) && c != 'q');
    return c;
}

char display_main_menu()
{
    /* instructions */
    clear_console();
    print_plate_console();
    display_centered_text_console("");
    display_centered_text_console("Moteur de Recherche");
    display_centered_text_console("");
    display_centered_text_console("(1) Utilisateur");
    display_centered_text_console("(2) Administrateur");
    display_centered_text_console("(3) A propos");
    display_centered_text_console("(q) Quitter");
    display_centered_text_console("");
    print_plate_console();
    return get_char_menu('4');
}

void display_user_menu()
{}

void display_admin_menu()
{}