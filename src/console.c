/*
Authors:    Constant ROUX,
            Julian TRANI,
            Peter PIRIOU--DEZY,
            Guillaume ROUSSIN,
            Nelson SANCHEZ
            
Date:       29/11/2021
*/

#include "console.h"

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
    if(fprintf(p_password_file, "%lu", password))
    {
        fprintf(stderr, "Error %d printing password %lu.\n\r", errno, password);
        return FALSE;
    }

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
    char conversion[2];

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
        display_centered_text_console("");
        display_centered_text_console("Indexation Image");
        display_centered_text_console("(3) Quantification");
        display_centered_text_console("");
        display_centered_text_console("Indexation Audio");
        display_centered_text_console("(4) Echantillons");
        display_centered_text_console("(5) Niveaux");
        display_centered_text_console("");
        display_centered_text_console("(q) Quitter");
        display_centered_text_console("");
        print_plate_console();
        c = get_char_menu('6');
        switch (c)
        {
        case '1':
            break;

        case '2':
            break; 
        case '3':
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

            fopen(LIST_BASE_IMAGE_PATH, "w");
            fopen(BASE_IMAGE_DESCRIPTOR_PATH, "w");
            if(automatic_indexing() == FALSE)
            {
                fprintf(stderr, "Error re-indexing images with new quantification.\n\r");
                return;
            }
            break;

        case '4':
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

            fopen(LIST_BASE_AUDIO_PATH, "w");
            fopen(BASE_AUDIO_DESCRIPTOR_PATH, "w");
            if(automatic_indexing() == FALSE)
            {
                fprintf(stderr, "Error re-indexing audio with new samples.\n\r");
                return;
            }
            break;
        
        case '5':
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

            fopen(LIST_BASE_AUDIO_PATH, "w");
            fopen(BASE_AUDIO_DESCRIPTOR_PATH, "w");
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
        display_centered_text_console("(1) Code couleur");
        display_centered_text_console("(2) Image couleur");
        display_centered_text_console("(3) Image niveaux de gris");
        display_centered_text_console("(q) Quitter");
        display_centered_text_console("");
        print_plate_console();
        c = get_char_menu('4');
        switch (c)
        {
        case '1':
            display_image_by_hexacode_research_menu();
            break;

        case '2':
            display_image_by_path_research_menu(TRUE);
            break;
        
        case '3':
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

Bool_e display_image_by_hexacode_research_menu()
{
    /* statements */
    Binary_search_tree_p confidence_tree;

    /* instructions */
    if(compare_image_hexacode("rouge", &confidence_tree) == FALSE)
    {
        fprintf(stderr, "Error comparing image by color.\n\r");
        return FALSE;
    }

    display_image_by_hexacode_result_menu(confidence_tree, "rouge");

    return TRUE;
}

Bool_e display_image_by_path_research_menu(Bool_e colored)
{
    /* statements */
    Binary_search_tree_p confidence_tree;
    char* path;
    int code;
    int ret;

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
        if(read_path(&path, &code) == FALSE)
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
                            display_image_result_menu(confidence_tree, path, TRUE);
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
                            display_image_result_menu(confidence_tree, path, FALSE);
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
            break;
        }
    }
    return TRUE;
}

void display_image_result_menu(Binary_search_tree_p confidence_tree, char* path, Bool_e colored)
{
    /*statements */
    char* file_name; 

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
    display_centered_text_console(str_concat("Requete : ", file_name));
    display_centered_text_console("");
    if(is_empty_binary_search_tree(confidence_tree) == FALSE)
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

void display_image_by_hexacode_result_menu(Binary_search_tree_p confidence_tree, char* color)
{
    /* instructions */
    clear_console();
    print_plate_console();
    display_centered_text_console("");
    display_centered_text_console(str_concat("Requete : ", color));
    display_centered_text_console("");
    if(is_empty_binary_search_tree(confidence_tree) == FALSE)
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

    /* initializations */
    one_result_existing = FALSE;

    /* instructions */
    clear_console();
    print_plate_console();
    file_name = strrchr(path, '/') + 1;
    strcpy(strrchr(file_name, '.'), ".wav");
    
    display_centered_text_console("");
    display_centered_text_console(str_concat("Requete : ", file_name));
    display_centered_text_console("");
    for(i = 0; i < size; i++)
    {
        if(is_empty_binary_search_tree(time_code_forest[i]) == FALSE)
        {
            if(one_result_existing == FALSE)
            {
                display_centered_text_console("Resultats");
            }
            one_result_existing = TRUE;
            display_centered_text_console(time_code_forest[i]->result.name);
            display_binary_search_tree(time_code_forest[i], AUDIO);
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
        if(read_path(&path, &code) == FALSE)
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
            break;
        }
    }
    return TRUE;
}