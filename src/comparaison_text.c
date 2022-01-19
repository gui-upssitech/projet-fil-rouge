/*
Authors:    Constant ROUX,
            Julian TRANI,
            Peter PIRIOU--DEZY,
            Guillaume ROUSSIN

            
Date:       29/11/2021
*/

#include "comparaison_text.h"

void init_keywords(Keywords_s* keywords)
{    
    keywords->keywords = NULL;
    keywords->size = 0;
}

Bool_e display_research_by_keyword(char *word)
{
    /* statements */
    FILE *p_indexing_table;
    char *p_line;
    char buf[MAX_MEMORY_STRING];
    char *name;
    unsigned long hash_code;
    unsigned int occurences;

    /* initalizations */

    /* instructions */
    p_indexing_table = fopen(INDEX_TABLE_TEXT_DESCRIPTOR_PATH, "r");
    if (p_indexing_table == NULL)
    {
        fprintf(stderr, "Error opening %s.\n\r", INDEX_TABLE_TEXT_DESCRIPTOR_PATH);
        return FALSE;
    }

    clear_console();
    print_plate_console();
    display_centered_text_console("");
    display_centered_text_console(str_concat("Requete : ", word));
    display_centered_text_console("");

    if (file_contains_substring(p_indexing_table, word, &p_line) == TRUE)
    {
        while (fgets(buf, sizeof(buf), p_indexing_table) != 0)
        {
            if (buf[0] == '\n')
            {
                break;
            }

            sscanf(buf, "%lu %u", &hash_code, &occurences);

            if (find_filename_from_id(hash_code, &name) == FALSE)
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

    if (fclose(p_indexing_table) == EOF)
    {
        fprintf(stderr, "Error closing file %s.\n\r", INDEX_TABLE_TEXT_DESCRIPTOR_PATH);
        return FALSE;
    }

    return TRUE;
}

Bool_e find_filename_from_id(unsigned long id, char **filename)
{
    FILE *p_list_base;
    char buf[MAX_MEMORY_STRING];
    unsigned long hash_code;

    p_list_base = fopen(LIST_BASE_TEXT_PATH, "r");
    if (p_list_base == NULL)
    {
        fprintf(stderr, "Error opening %s.\n\r", LIST_BASE_TEXT_PATH);
        return FALSE;
    }

    while (!feof(p_list_base))
    {
        fscanf(p_list_base, "%s %lu\n", buf, &hash_code);
        if (hash_code == id)
        {
            *filename = (char *)malloc(strlen(buf) * sizeof(char));
            strcpy(*filename, buf);
            return TRUE;
        }
    }

    if (fclose(p_list_base) == EOF)
    {
        fprintf(stderr, "Error closing %s.\n\r", LIST_BASE_TEXT_PATH);
        return FALSE;
    }

    return FALSE;
}

Bool_e display_research_by_text(char *path)
{
    /* statements */
    Text_descriptor_s desc;
    char word[MAX_MEMORY_STRING];
    char *line;
    unsigned int num_occurences;
    unsigned int i;

    Keywords_s keywords;

    /* initalizations */
    init_keywords(&keywords);

    /* STEP 1 : Indexing the text in param */
    if(index_text(path, &desc) == FALSE)
    {
        fprintf(stderr, "Error indexing text research by text %s", path);
        return FALSE;
    }

    /*Source : https://stackoverflow.com/questions/17983005/c-how-to-read-a-string-line-by-line */
    /* Read line one by one and add the word/occurence to the tree */
    while (desc.descriptor_contents)
    {
        char *new_buffer = strchr(desc.descriptor_contents, '\n');
        size_t line_len = new_buffer ? (size_t)(new_buffer - desc.descriptor_contents) : strlen(desc.descriptor_contents);
        line = (char *)malloc(line_len + 1);

        if (line == NULL)
        {
            fprintf(stderr, "Error : failed to allocate memory.\n\r");
            return FALSE;
        }

        memcpy(line, desc.descriptor_contents, line_len);
        line[line_len] = '\0'; /* nul terminate the string to avoid errors */

        /* Line treatment - Start by skipping the first line and last two lines */
        if (strchr(line, ' '))
        {
            sscanf(line, "%s %u\n", word, &num_occurences);
            // printf("%s %u\n", word, num_occurences);

            /* step 1 : memory allocation */
            keywords.keywords = (Keyword_s *)realloc(keywords.keywords, sizeof(Keyword_s) * (keywords.size + 1));
            if (keywords.keywords == NULL)
            {
                return FALSE;
            }

            keywords.keywords[keywords.size].word = (char* )malloc(sizeof(char* ) * strlen(word));
            if (keywords.keywords[keywords.size].word == NULL)
            {
                return FALSE;
            }

            strcpy(keywords.keywords[keywords.size].word, word);
            keywords.keywords[keywords.size].occurences = num_occurences;

            keywords.size++;  
        }

        free(line);
        desc.descriptor_contents = new_buffer ? (new_buffer + 1) : NULL; /* Remove the line (the +1 skips the \n) */
    }

    /* step 2 : compute all weights for each keyword */
    for(i = 0; i < keywords.size; i++)
    {
        keywords.keywords[i].word_weight = (float) keywords.keywords[i].occurences / (float) keywords.keywords[0].occurences;
    }

    /* STEP 2 :  */

    /* STEP 3 :  */

    /* instructions */
    return TRUE;
}