/*
Authors:    Constant ROUX,
            Julian TRANI,
            Peter PIRIOU--DEZY,
            Guillaume ROUSSIN
            
            
Date:       29/11/2021
*/

#include "console.h"
#include "comparaison_text.h"

void clear_console()
{
    // printf("\033[H\033[2J");
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
    unsigned int i;

    /* instructions */
    for(i = 0; i < blank_size; i++)
    {
        printf("%s", SPACE);
    }
}

void display_centered_text_console(const char* p_text)
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
    int code;
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

    display_centered_text_console("Taper Echap pour quitter");
    
    display_centered_text_console("");
    print_plate_console();
    password = get_hashed_password(&code);
    if(code == 1)
    {
        fprintf(p_password_file, "%lu", password);

        if(fclose(p_password_file) == EOF)
        {
            fprintf(stderr, "Error %d closing the file %s.\n\r", errno, PASSWORD_RELATIVE_PATH);
            return FALSE;
        }
    }
    
    return TRUE;
}

void display_login_menu()
{
    /* statements */
    int code;
    unsigned long password;
    static unsigned char nb_try = 1;
    char str[2];
    char display_string[MAX_MEMORY_STRING];

    /* instructions */
    sprintf(str, "%d", MAX_TRY_PASSWORD - nb_try + 1);
    clear_console();
    print_plate_console();
    display_centered_text_console("");
    sprintf(display_string, "Mot de passe (%s %s)", str, (str[0] == '1') ? "essai restant" : "essais restants");
    display_centered_text_console(display_string);
    display_centered_text_console("Taper Echap pour quitter");
    display_centered_text_console("");
    print_plate_console();

    /* instructions */
    password = get_hashed_password(&code);
    if(code == 1)
    {
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
    else
    {
        nb_try = 1;
        return;
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
            display_audio_by_path_research_menu();
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
        display_centered_text_console("(3) Modifier mot de passe");
        display_centered_text_console("(q) Quitter");
        display_centered_text_console("");
        print_plate_console();
        c = get_char_menu('5');
        switch (c)
        {
        case '1':
            display_indexation_admin_menu();
            break;

        case '2':
            display_comparison_admin_menu();
            break;

        case '3':
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

void display_indexation_admin_menu()
{
    /* statements */
    Bool_e ret;
    char c;
    long value;
    char conversion[MAX_MEMORY_STRING];

    /* instructions */
    while(1)
    {
        clear_console();
        print_plate_console();
        display_centered_text_console("");
        display_centered_text_console("Parametres indexation");
        display_centered_text_console("");
        display_centered_text_console("Indexation Texte");
        display_centered_text_console("(1) Mode");
        display_centered_text_console("(2) Seuil");
        display_centered_text_console("(3) Debug");
        display_centered_text_console("(4) Limite index");
        display_centered_text_console("");
        display_centered_text_console("Indexation Image");
        display_centered_text_console("(5) Quantification");
        display_centered_text_console("");
        display_centered_text_console("Indexation Audio");
        display_centered_text_console("(6) Echantillons");
        display_centered_text_console("(7) Niveaux");
        display_centered_text_console("");
        display_centered_text_console("(q) Quitter");
        display_centered_text_console("");
        print_plate_console();
        c = get_char_menu('8');
        switch (c)
        {
        case '1':
            do
            {
                printf("Veuillez choisir le mode (0 pour %s ou 1 pour %s) : ", LIMIT_MODE, THRESHOLD_MODE);
                ret = read_integer(&value);
                printf("\33[1A\33[2K\r");
            } while(ret != 0 && ret != 1);

            if(sprintf(conversion, "%ld", value) == EOF)
            {
                fprintf(stderr, "Error %d converting text mode value integer to char array.\n\r", errno);
                return;
            }

            if(save_configuration("indexing_text_filter_mode", conversion) == FALSE)
            {
                fprintf(stderr, "Error saving new text mode value.\n\r");
                return;
            }

            fclose(fopen(LIST_BASE_TEXT_PATH, "w"));
            fclose(fopen(BASE_TEXT_DESCRIPTOR_PATH, "w"));
            fclose(fopen(INDEX_TABLE_TEXT_DESCRIPTOR_PATH, "w"));
            if(automatic_indexing() == FALSE)
            {
                fprintf(stderr, "Error re-indexing text with new mode.\n\r");
                return;
            }
            break;

        case '2':
            do
            {
                printf("Veuillez insérer une valeur entre %d et %d : ", MIN_FILTER_SIZE, MAX_FILTER_SIZE);
                ret = read_integer(&value);
                printf("\33[1A\33[2K\r");
            } while(value < MIN_FILTER_SIZE || value > MAX_FILTER_SIZE || ret == FALSE);

            if(sprintf(conversion, "%ld", value) == EOF)
            {
                fprintf(stderr, "Error %d converting filter text value integer to char array.\n\r", errno);
                return;
            }

            if(save_configuration("indexing_text_filter_value", conversion) == FALSE)
            {
                fprintf(stderr, "Error saving new text filter value.\n\r");
                return;
            }

            fclose(fopen(LIST_BASE_TEXT_PATH, "w"));
            fclose(fopen(BASE_TEXT_DESCRIPTOR_PATH, "w"));
            fclose(fopen(INDEX_TABLE_TEXT_DESCRIPTOR_PATH, "w"));
            if(automatic_indexing() == FALSE)
            {
                fprintf(stderr, "Error re-indexing text with new mode.\n\r");
                return;
            }
            break;

        case '3':
            do
            {
                printf("Activer le debug (0 pour desactiver ou 1 pour activer) : ");
                ret = read_integer(&value);
                printf("\33[1A\33[2K\r");
            } while(ret != 0 && ret != 1);

            if(sprintf(conversion, "%ld", value) == EOF)
            {
                fprintf(stderr, "Error %d converting text debug value integer to char array.\n\r", errno);
                return;
            }

            if(save_configuration("indexing_text_debug", conversion) == FALSE)
            {
                fprintf(stderr, "Error saving new debug mode value.\n\r");
                return;
            }

            fclose(fopen(LIST_BASE_TEXT_PATH, "w"));
            fclose(fopen(BASE_TEXT_DESCRIPTOR_PATH, "w"));
            fclose(fopen(INDEX_TABLE_TEXT_DESCRIPTOR_PATH, "w"));
            if(automatic_indexing() == FALSE)
            {
                fprintf(stderr, "Error re-indexing text with new debug mode.\n\r");
                return;
            }
            break;

        case '4':
            do
            {
                printf("Veuillez insérer une valeur entre %d et %d : ", MIN_FILTER_SIZE, MAX_FILTER_SIZE);
                ret = read_integer(&value);
                printf("\33[1A\33[2K\r");
            } while(value < MIN_FILTER_SIZE || value > MAX_FILTER_SIZE || ret == FALSE);

            if(sprintf(conversion, "%ld", value) == EOF)
            {
                fprintf(stderr, "Error %d converting index text value integer to char array.\n\r", errno);
                return;
            }

            if(save_configuration("indexing_text_number_table_index", conversion) == FALSE)
            {
                fprintf(stderr, "Error saving new text index value.\n\r");
                return;
            }

            fclose(fopen(LIST_BASE_TEXT_PATH, "w"));
            fclose(fopen(BASE_TEXT_DESCRIPTOR_PATH, "w"));
            fclose(fopen(INDEX_TABLE_TEXT_DESCRIPTOR_PATH, "w"));
            if(automatic_indexing() == FALSE)
            {
                fprintf(stderr, "Error re-indexing text with new index text value.\n\r");
                return;
            }
            break;

        case '5':
            do
            {
                printf("Veuillez insérer une valeur entre %d et %d : ", MIN_QUANTIFICATION_SIZE, MAX_QUANTIFICATION_SIZE);
                ret = read_integer(&value);
                printf("\33[1A\33[2K\r");
            } while(value < MIN_QUANTIFICATION_SIZE || value > MAX_QUANTIFICATION_SIZE || ret == FALSE);

            if(sprintf(conversion, "%ld", value) == EOF)
            {
                fprintf(stderr, "Error %d converting quantification value integer to char array.\n\r", errno);
                return;
            }

            if(save_configuration("indexing_image_quantification", conversion) == FALSE)
            {
                fprintf(stderr, "Error saving new image quantification value.\n\r");
                return;
            }

            fclose(fopen(LIST_BASE_IMAGE_PATH, "w"));
            fclose(fopen(BASE_IMAGE_DESCRIPTOR_PATH, "w"));
            if(automatic_indexing() == FALSE)
            {
                fprintf(stderr, "Error re-indexing images with new quantification.\n\r");
                return;
            }
            break;

        case '6':
            do
            {
                printf("Veuillez insérer une puissance de 2 (minimum 256) : ");
                ret = read_integer(&value);
                printf("\33[1A\33[2K\r");
            } while((value & (value - 1)) != 0 || ret == FALSE || value < 256);

            if(sprintf(conversion, "%ld", value) == EOF)
            {
                fprintf(stderr, "Error %d converting samples audio value integer to char array.\n\r", errno);
                return;
            }

            if(save_configuration("indexing_audio_samples", conversion) == FALSE)
            {
                fprintf(stderr, "Error saving new samples audio value.\n\r");
                return;
            }

            fclose(fopen(LIST_BASE_AUDIO_PATH, "w"));
            fclose(fopen(BASE_AUDIO_DESCRIPTOR_PATH, "w"));
            if(automatic_indexing() == FALSE)
            {
                fprintf(stderr, "Error re-indexing audio with new samples.\n\r");
                return;
            }
            break;
        
        case '7':
            do
            {
                printf("Veuillez insérer une valeur entre %d et %d : ", MIN_LEVELS_SIZE, MAX_LEVELS_SIZE);
                ret = read_integer(&value);
                printf("\33[1A\33[2K\r");
            } while(value < MIN_LEVELS_SIZE || value > MAX_LEVELS_SIZE || ret == FALSE);

            if(sprintf(conversion, "%ld", value) == EOF)
            {
                fprintf(stderr, "Error %d converting audio levels value integer to char array.\n\r", errno);
                return;
            }

            if(save_configuration("indexing_audio_interval", conversion) == FALSE)
            {
                fprintf(stderr, "Error saving new audio levels value.\n\r");
                return;
            }

            fclose(fopen(LIST_BASE_AUDIO_PATH, "w"));
            fclose(fopen(BASE_AUDIO_DESCRIPTOR_PATH, "w"));
            if(automatic_indexing() == FALSE)
            {
                fprintf(stderr, "Error re-indexing audio with new levels.\n\r");
                return;
            }
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

void display_comparison_admin_menu()
{
    /* statements */
    Bool_e ret;
    char c;
    long value;
    char conversion[MAX_MEMORY_STRING];

    /* instructions */
    while(1)
    {
        clear_console();
        print_plate_console();
        display_centered_text_console("");
        display_centered_text_console("Parametres comparaison");
        display_centered_text_console("");
        display_centered_text_console("Comparaison Image");
        display_centered_text_console("(1) Seuil");
        display_centered_text_console("");
        display_centered_text_console("Comparaison Audio");
        display_centered_text_console("(2) Pas");
        display_centered_text_console("(3) Seuil");
        display_centered_text_console("");
        display_centered_text_console("(q) Quitter");
        display_centered_text_console("");
        print_plate_console();
        c = get_char_menu('4');
        switch (c)
        {
        case '1':
            do
            {
                printf("Veuillez insérer une valeur entre %d et %d : ", 0, 100);
                ret = read_integer(&value);
                printf("\33[1A\33[2K\r");
            } while(value < 0 || value > 100 || ret == FALSE);

            if(sprintf(conversion, "%ld", value) == EOF)
            {
                fprintf(stderr, "Error %d converting image threshold value integer to char array.\n\r", errno);
                return;
            }

            if(save_configuration("comparison_image_threshold", conversion) == FALSE)
            {
                fprintf(stderr, "Error saving new image threshold value.\n\r");
                return;
            }
            break;
        
        case '2':
            do
            {
                printf("Veuillez insérer une valeur entre %d et %d : ", 1, 10);
                ret = read_integer(&value);
                printf("\33[1A\33[2K\r");
            } while(value < 1 || value > 10 || ret == FALSE);

            if(sprintf(conversion, "%ld", value) == EOF)
            {
                fprintf(stderr, "Error %d converting audio step value integer to char array.\n\r", errno);
                return;
            }

            if(save_configuration("comparison_audio_step", conversion) == FALSE)
            {
                fprintf(stderr, "Error saving new audio step value.\n\r");
                return;
            }
            break;

        case '3':
            do
            {
                printf("Veuillez insérer une valeur entre %d et %d : ", 0, 100);
                ret = read_integer(&value);
                printf("\33[1A\33[2K\r");
            } while(value < 0 || value > 100 || ret == FALSE);

            if(sprintf(conversion, "%ld", value) == EOF)
            {
                fprintf(stderr, "Error %d converting audio threshold value integer to char array.\n\r", errno);
                return;
            }

            if(save_configuration("comparison_audio_threshold", conversion) == FALSE)
            {
                fprintf(stderr, "Error saving new audio threshold value.\n\r");
                return;
            }
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

Bool_e display_text_research_by_keyword_menu()
{
    /* statements */
    char* word;
    int code;

    /* initalizations */

    /* instructions */
    while(1)
    {
        clear_console();
        print_plate_console();
        display_centered_text_console("");
        display_centered_text_console("Recherche par mot-clef");
        display_centered_text_console("");
        display_centered_text_console("Inserer le mot a rechercher");
        display_centered_text_console("Taper Echap pour quitter");
        display_centered_text_console("");
        print_plate_console();
        if(read_string(&word, &code) == FALSE)
        {
            fprintf(stderr, "Error reading word research file.\n\r");
            return FALSE;
        }

        if(code == 0)
        {
            display_research_by_keyword(word);
        }
        else
        {
            free(word);
            break;
        }
    }
    return TRUE;
}

Bool_e display_text_research_by_text_menu()
{
    /* statements */
    char* path;
    int code;
    int ret ; 

    /* initalizations */
    ret = 0 ;

    /* instructions */
    while(1)
    {
        clear_console();
        print_plate_console();
        display_centered_text_console("");
        display_centered_text_console("Recherche par texte");
        display_centered_text_console("");
        if(ret != 0)
        {
            if(ret == 1)
            {
                display_centered_text_console("Fichier inexistant ou invalide");
            }
            else
            {
                display_centered_text_console("Fichier au mauvais format");
            }
            
            display_centered_text_console("");
            ret = 0;
        }
        display_centered_text_console("Inserer le nom du fichier texte");
        display_centered_text_console("Taper Echap pour quitter");
        display_centered_text_console("");
        print_plate_console();
        if(read_string(&path, &code) == FALSE)
        {
            fprintf(stderr, "Error reading word research file.\n\r");
            return FALSE;
        }

        if(code == 0)
        {            
            if(is_regular_file(path) == TRUE)
            {
                if(is_extension_file(path, "xml") == TRUE)
                {
                    display_research_by_text(path);
                }
                else
                {
                    ret = 2;
                }
            }
            else
            {
                ret = 1;
            }
            
        }
        else
        {
            free(path);
            break;
        }
        
        free(path);
    }
    
    return TRUE;
}

void display_text_research_menu()
{
    /* statements */
    char c;

    /* instructions */
    while(1)
    {
        clear_console();
        print_plate_console();
        display_centered_text_console("");
        display_centered_text_console("Menu Texte");
        display_centered_text_console("");
        display_centered_text_console(" Recherche par :");
        display_centered_text_console("(1) Mot-clef");
        display_centered_text_console("(2) Texte");
        display_centered_text_console("(q) Quitter");
        display_centered_text_console("");
        print_plate_console();
        c = get_char_menu('3');
        switch (c)
        {
        case '1':
            display_text_research_by_keyword_menu();
            break;

        case '2':         
            display_text_research_by_text_menu();    
            break;

        case 'q':
        default:
            return;
            break;
        }
    }

}

void display_image_research_menu()
{
    /* statements */
    char c;

    /* instructions */
    while(1)
    {
        clear_console();
        print_plate_console();
        display_centered_text_console("");
        display_centered_text_console("Menu Image");
        display_centered_text_console("");
        display_centered_text_console("Recherche par :");
        display_centered_text_console("(1) Image couleur");
        display_centered_text_console("(2) Image niveaux de gris");
        display_centered_text_console("(q) Quitter");
        display_centered_text_console("");
        print_plate_console();
        c = get_char_menu('3');
        switch (c)
        {
        case '1':
            display_image_by_path_research_menu(TRUE);
            break;
        
        case '2':
            display_image_by_path_research_menu(FALSE);
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

Bool_e display_image_by_path_research_menu(Bool_e colored)
{
    /* statements */
    Binary_search_tree_p confidence_tree;
    char* path;
    int code;
    int ret;
    Result_s result;

    /* initalizations */
    ret = 0;

    /* instructions */
    while(1)
    {
        clear_console();
        print_plate_console();
        display_centered_text_console("");
        if(colored == TRUE)
        {        
            display_centered_text_console("Recherche par image couleur");
        }
        else
        {
            display_centered_text_console("Recherche par image niveaux de gris");
        }
        display_centered_text_console("");
        if(ret != 0)
        {
            if(ret == 1)
            {
                display_centered_text_console("Fichier inexistant ou invalide");
            }
            else
            {
                display_centered_text_console("Fichier au mauvais format");
            }
            
            display_centered_text_console("");
            ret = 0;
        }
        display_centered_text_console("Inserer le chemin du fichier");
        display_centered_text_console("Taper Echap pour quitter");
        display_centered_text_console("");
        print_plate_console();
        if(read_string(&path, &code) == FALSE)
        {
            fprintf(stderr, "Error reading path file.\n\r");
            return FALSE;
        }

        if(code == 0)
        {
            if(is_regular_file(path) == TRUE)
            {
                if(colored == TRUE)
                {
                    if(is_extension_file(path, "jpg") == TRUE)
                    {
                        strcpy(strrchr(path, '.'), ".txt");
                        if(compare_image_files(path, &confidence_tree, TRUE) == TRUE)
                        {
                            get_max_tree(&result, confidence_tree);
                            open_file(RGB_BASE_PATH, result.name);
                            display_image_result_menu(&confidence_tree, path, TRUE);   
                            free_binary_search_tree(&confidence_tree);
                        }
                        else
                        {
                            fprintf(stderr, "Error comparing image file \"%s\".\n\r", path);
                            return FALSE;
                        }
                    }
                    else
                    {
                        ret = 2;
                    }
                }
                else
                {
                    if(is_extension_file(path, "bmp") == TRUE)
                    {
                        strcpy(strrchr(path, '.'), ".txt");
                        if(compare_image_files(path, &confidence_tree, FALSE) == TRUE)
                        {
                            get_max_tree(&result, confidence_tree);
                            open_file(NB_BASE_PATH, result.name);
                            display_image_result_menu(&confidence_tree, path, FALSE);
                            free_binary_search_tree(&confidence_tree); 
                        }
                        else
                        {
                            fprintf(stderr, "Error comparing image file \"%s\".\n\r", path);
                            return FALSE;
                        }
                    }
                    else
                    {
                        ret = 2;
                    }
                }
            }
            else
            {
                ret = 1;
            }
        }
        else
        {
            free(path);
            break;
        }
        free(path);
    }
    
    return TRUE;
}

void display_image_result_menu(Binary_search_tree_p* confidence_tree, char* path, Bool_e colored)
{
    /*statements */
    char* file_name; 
    char string[MAX_MEMORY_STRING];

    /* instructions */
    clear_console();
    print_plate_console();
    file_name = strrchr(path, '/') + 1;
    if(colored == TRUE)
    {
        strcpy(strrchr(file_name, '.'), ".jpg");
    }
    else
    {
        strcpy(strrchr(file_name, '.'), ".bmp");
    }
    
    display_centered_text_console("");
    sprintf(string, "Requete : %s", file_name);
    display_centered_text_console(string);
    display_centered_text_console("");
    if(is_empty_binary_search_tree(*confidence_tree) == FALSE)
    {
        display_centered_text_console("Resultats");
        display_binary_search_tree(confidence_tree, IMAGE);
    }
    else
    {
        display_centered_text_console("Aucun resultat");
    }
    display_centered_text_console("");
    display_centered_text_console("Appuyez sur n'importe quelle touche pour quitter...");
    display_centered_text_console("");
    print_plate_console();
    getch();
}

void display_audio_result_menu(Binary_search_tree_p* time_code_forest, unsigned int size, char* path)
{
    /* statements */
    char* file_name; 
    unsigned int i;
    Bool_e one_result_existing;
    Result_s max_confidence, current_confidence;
    char command[2 * MAX_MEMORY_STRING];
    char string[MAX_MEMORY_STRING];

    /* initializations */
    one_result_existing = FALSE;
    max_confidence.confidence = 0.0;

    /* instructions */
    clear_console();
    print_plate_console();
    file_name = strrchr(path, '/') + 1;
    strcpy(strrchr(file_name, '.'), ".wav");
    
    display_centered_text_console("");
    sprintf(string, "Requete : %s", file_name);
    display_centered_text_console(string);
    display_centered_text_console("");
    for(i = 0; i < size; i++)
    {
        if(is_empty_binary_search_tree(time_code_forest[i]) == FALSE)
        {
            get_max_confidence_audio_tree(&current_confidence, time_code_forest[i]);
            if(current_confidence.confidence > max_confidence.confidence)
            {
                max_confidence = current_confidence;
            }

            if(one_result_existing == FALSE)
            {
                display_centered_text_console("Resultats");
            }
            one_result_existing = TRUE;
            display_centered_text_console(time_code_forest[i]->result.name);
            display_binary_search_tree(&(time_code_forest[i]), AUDIO);
            display_centered_text_console("");
        }
    }

    if(one_result_existing == FALSE)
    {
        display_centered_text_console("Aucun resultat");
        display_centered_text_console("");
    }
    
    display_centered_text_console("Appuyez sur n'importe quelle touche pour quitter...");
    display_centered_text_console("");
    print_plate_console();

    if(one_result_existing == TRUE)
    {
        sprintf(command, "ffplay %s%s -ss %d > /dev/null 2> /dev/null", SOUND_BASE_PATH, max_confidence.name, max_confidence.time_code);
        system(command);
    }

    getch();
}

Bool_e display_audio_by_path_research_menu()
{
    /* statements */
    Binary_search_tree_p* time_code_forest;
    unsigned int size;
    char* path;
    int code;
    int ret;
    unsigned int i;

    /* initalizations */
    ret = 0;

    /* instructions */
    while(1)
    {
        clear_console();
        print_plate_console();
        display_centered_text_console("");      
        display_centered_text_console("Recherche Audio");
        display_centered_text_console("");
        if(ret != 0)
        {
            if(ret == 1)
            {
                display_centered_text_console("Fichier inexistant ou invalide");
            }
            else
            {
                display_centered_text_console("Fichier au mauvais format");
            }
            
            display_centered_text_console("");
            ret = 0;
        }
        display_centered_text_console("Inserer le chemin du fichier");
        display_centered_text_console("Taper Echap pour quitter");
        display_centered_text_console("");
        print_plate_console();
        if(read_string(&path, &code) == FALSE)
        {
            fprintf(stderr, "Error reading path file.\n\r");
            return FALSE;
        }

        if(code == 0)
        {
            if(is_regular_file(path) == TRUE)
          {
                if(is_extension_file(path, "wav") == TRUE)
                {
                    strcpy(strrchr(path, '.'), ".bin");
                    if(compare_audio_files(path, &time_code_forest, &size) == TRUE)
                    {
                        display_audio_result_menu(time_code_forest, size, path);
                        for(i = 0; i < size; i++)
                        {
                            free_binary_search_tree(&(time_code_forest[i]));
                        }
                        free(time_code_forest);
                        free(path);
                    }
                    else
                    {
                        fprintf(stderr, "Error comparing audio file \"%s\".\n\r", path);
                        return FALSE;
                    }
                }
                else
                {
                    ret = 2;
                }
            }
            else
            {
                ret = 1;
            }
        }
        else
        {
            free(path);
            break;
        }
    }
    return TRUE;
}