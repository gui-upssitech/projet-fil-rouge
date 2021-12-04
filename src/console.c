/*
Authors:    Constant ROUX,
            Julian TRANI,
            Peter PIRIOU--DEZY,
            Guillaume ROUSSIN,
            Nelson SANCHEZ
            
Date:       29/11/2021
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>

#include "../inc/console.h"
#include "../inc/admin.h"


void clear_console()
{
    system("clear");
}

void print_plate_console()
{
    /* statements */
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
    /* statements */
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
        fprintf(stderr, "Error overflow writing line menu.\n\r");
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

void display_main_menu()
{
    /* statements */
    char c;
    struct stat s_fileStat;

    /* instructions */
    while(1)
    {
        stat(PASSWORD_RELATIVE_PATH, &s_fileStat);
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
        c = get_char_menu('4');
        switch (c)
        {
        case '1':
            display_user_menu();
            break;

        case '2':
            if(s_fileStat.st_size != 0)
            {
                display_login_menu();
            }
            else
            {
                if(display_new_pwd_menu(TRUE) == FALSE)
                {
                    fprintf(stderr, "Error during password initialization.\n\r");
                    return;
                }
            }
            break;

        case '3':
            display_about_menu();
            break;

        case 'q':
            return;
            break;
        
        default:
            return;
            break;
        }
    }
}

Bool_e display_new_pwd_menu(Bool_e first_password)
{
    /* statements */
    FILE* p_password_file;
    unsigned long password;

    /* initializations */
    p_password_file = fopen(PASSWORD_RELATIVE_PATH, "w");

    /* instructions */
    if(p_password_file == NULL)
    {
        fprintf(stderr, "Error %d opening %s.\n\r", errno, PASSWORD_RELATIVE_PATH);
        return FALSE;
    }
    clear_console();
    print_plate_console();
    display_centered_text_console("");
    if(first_password == TRUE)
    {
        display_centered_text_console("Initialisation mot de passe");
    }
    else
    {
        display_centered_text_console("Nouveau mot de passe");
    }
    
    display_centered_text_console("");
    print_plate_console();
    password = get_hashed_password();
    fprintf(p_password_file, "%lu", password);

    if(fclose(p_password_file) == EOF)
    {
        fprintf(stderr, "Error %d closing the file %s.\n\r", errno, PASSWORD_RELATIVE_PATH);
        return FALSE;
    }

    return TRUE;
}

void display_login_menu()
{
    /* statements */
    unsigned long password;
    static unsigned char nb_try = 1;
    char str[2];

    /* instructions */
    sprintf(str, "%d", MAX_TRY_PASSWORD - nb_try + 1);
    clear_console();
    print_plate_console();
    display_centered_text_console("");
    display_centered_text_console(str_concat(str_concat("Mot de passe (", str), (str[0] == '1') ? " essai restant)" : " essais restants)"));
    display_centered_text_console("");
    print_plate_console();

    /* instructions */
    password = get_hashed_password();
    if(is_password_valid(password) == TRUE)
    {
        nb_try = 1;
        display_admin_menu();
    }
    else
    {
        if(nb_try < MAX_TRY_PASSWORD)
        {
            nb_try++;
            display_login_menu();
        }
        else
        {
            nb_try = 1;
            return;
        }
    }
} 

void display_user_menu()
{
    /* statements */
    char c;

    /* instructions */
    while(1)
    {
        clear_console();
        print_plate_console();
        display_centered_text_console("");
        display_centered_text_console("Menu Utilisateur");
        display_centered_text_console("");
        display_centered_text_console("Type de recherche :");
        display_centered_text_console("(1) Texte");
        display_centered_text_console("(2) Image");
        display_centered_text_console("(3) Audio");
        display_centered_text_console("(q) Quitter");
        display_centered_text_console("");
        print_plate_console();
        c = get_char_menu('4');
        switch (c)
        {
        case '1':
            display_text_research_menu();
            break;

        case '2':
            display_image_research_menu();
            break;

        case '3':
            display_audio_research_menu();
            break;

        case 'q':
            return;
            break;
        
        default:
            return;
            break;
        }
    }
}

void display_admin_menu()
{
    /* statements */
    char c;

    /* instructions */
    while(1)
    {
        clear_console();
        print_plate_console();
        display_centered_text_console("");
        display_centered_text_console("Menu Administrateur");
        display_centered_text_console("");
        display_centered_text_console("Fonctions :");
        display_centered_text_console("(1) Indexation");
        display_centered_text_console("(2) Comparaison");
        display_centered_text_console("(3) Moteur de recherche");
        display_centered_text_console("(4) Modifier mot de passe");
        display_centered_text_console("(q) Quitter");
        display_centered_text_console("");
        print_plate_console();
        c = get_char_menu('5');
        switch (c)
        {
        case '1':
            display_text_research_menu();
            break;

        case '2':
            display_image_research_menu();
            break;

        case '3':
            display_audio_research_menu();
            break;

        case '4':
            display_new_pwd_menu(FALSE);
            break;

        case 'q':
            return;
            break;
        
        default:
            return;
            break;
        }
    }

}

void display_about_menu()
{
    /* statements */
    char c;

    /* instructions */
    while(1)
    {
        clear_console();
        print_plate_console();
        display_centered_text_console("");
        display_centered_text_console("A propos");
        display_centered_text_console("");
        display_centered_text_console("Auteurs");
        display_centered_text_console("Julian TRANI");
        display_centered_text_console("Guillaume ROUSSIN");
        display_centered_text_console("Peter PIRIOU--DEZY");
        display_centered_text_console("Constant ROUX");
        display_centered_text_console("Nelson SANCHEZ");
        display_centered_text_console("");
        display_centered_text_console("Version");
        display_centered_text_console("0.1");
        display_centered_text_console("");
        display_centered_text_console("(q) Quitter");
        display_centered_text_console("");
        print_plate_console();
        c = get_char_menu('4');
        switch (c)
        {
        case 'q':
            return;
            break;
        
        default:
            return;
            break;
        }
    }
}

void display_text_research_menu()
{

}

void display_image_research_menu()
{

}

void display_audio_research_menu()
{

}