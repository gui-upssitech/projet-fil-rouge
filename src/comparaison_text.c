/*
Authors:    Constant ROUX,
            Julian TRANI,
            Peter PIRIOU--DEZY,
            Guillaume ROUSSIN

            
Date:       29/11/2021
*/

#include "comparaison_text.h"

Bool_e display_research_by_keyword(char* word)
{
    /* statements */
    FILE* p_indexing_table;
    char* p_line;
    char buf[MAX_MEMORY_STRING];
    char* name;
    unsigned long hash_code;
    unsigned int occurences;

    /* initalizations */


    /* instructions */
    p_indexing_table = fopen(INDEX_TABLE_TEXT_DESCRIPTOR_PATH, "r");
    if(p_indexing_table == NULL)
    {
        fprintf(stderr, "Error opening %s.\n\r", INDEX_TABLE_TEXT_DESCRIPTOR_PATH);
        return FALSE;
    }

    clear_console();
    print_plate_console();
    display_centered_text_console("");
    display_centered_text_console(str_concat("Requete : ", word));
    display_centered_text_console("");

    if(file_contains_substring(p_indexing_table, word, &p_line) == TRUE)
    {
        while(fgets(buf, sizeof(buf), p_indexing_table) != 0)
        {
            if(buf[0] == '\n')
            {
                break;
            }

            sscanf(buf, "%lu %u", &hash_code, &occurences);

            if(find_filename_from_id(hash_code, &name) == FALSE)
            {
                fprintf(stderr, "Error file not found in the base.\n\r");
                return FALSE;
            }
            sprintf(buf, "%s %u", name, occurences);
            display_centered_text_console(buf);
        }
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

    if(fclose(p_indexing_table) == EOF)
    {
        fprintf(stderr, "Error closing file %s.\n\r", INDEX_TABLE_TEXT_DESCRIPTOR_PATH);
        return FALSE;
    }

    return TRUE;
}

Bool_e find_filename_from_id(unsigned long id, char** filename)
{
    FILE* p_list_base;
    char buf[MAX_MEMORY_STRING];
    unsigned long hash_code;

    p_list_base = fopen(LIST_BASE_TEXT_PATH, "r");
    if(p_list_base == NULL)
    {
        fprintf(stderr, "Error opening %s.\n\r", LIST_BASE_TEXT_PATH);
        return FALSE;
    }

    while(!feof(p_list_base))
    {
        fscanf(p_list_base, "%s %lu\n", buf, &hash_code);
        if(hash_code == id)
        {
            *filename = (char*) malloc(strlen(buf) * sizeof(char));
            strcpy(*filename, buf);
            return TRUE;
        }
    }

    if(fclose(p_list_base) == EOF)
    {
        fprintf(stderr, "Error closing %s.\n\r", LIST_BASE_TEXT_PATH);
        return FALSE;
    }

    return FALSE;
}