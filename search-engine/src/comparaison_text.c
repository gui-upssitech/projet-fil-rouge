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
    keywords->score_texts = NULL;
    keywords->size_scores = 0;
}

Bool_e display_research_by_keyword(char* word)
{
    /* statements */
    FILE* p_indexing_table;
    char* p_line;
    char buf[MAX_MEMORY_STRING];
    char* name;
    unsigned long hash_code;
    unsigned int occurences;
    Bool_e first;
    char string[MAX_MEMORY_STRING];

    /* initalizations */
    first = TRUE;

    /* instructions */
    p_indexing_table = fopen(INDEX_TABLE_TEXT_DESCRIPTOR_PATH, "r");
    if (p_indexing_table == NULL)
    {
        fprintf(stderr, "Error opening %s.\n\r", INDEX_TABLE_TEXT_DESCRIPTOR_PATH);
        return FALSE;
    }

    #if defined(TEXTUAL)
    clear_console();
    print_plate_console();
    display_centered_text_console("");
    sprintf(string, "Requete : %s", word);
    display_centered_text_console(string);
    display_centered_text_console("");
    #endif


    if (file_contains_string(p_indexing_table, word, &p_line) == TRUE)
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

            if(first == TRUE)
            {
                open_file(TEXT_BASE_PATH, name);
                first = FALSE;
            }
            sprintf(buf, "%s %u", name, occurences);

            #if defined(TEXTUAL)
            display_centered_text_console(buf);
            #elif defined(GRAPHICAL)
            printf("%s\n", buf);
            #endif 

            free(name);
        }
    }
    else
    {
        #if defined(TEXTUAL)
        display_centered_text_console("Aucun resultat");
        #endif
    }

    #if defined(TEXTUAL)
    display_centered_text_console("");
    display_centered_text_console("Appuyez sur n'importe quelle touche pour quitter...");
    display_centered_text_console("");
    print_plate_console();
    getch();
    #endif

    if (fclose(p_indexing_table) == EOF)
    {
        fprintf(stderr, "Error closing file %s.\n\r", INDEX_TABLE_TEXT_DESCRIPTOR_PATH);
        return FALSE;
    }

    #if defined(TEXTUAL)
    free(word);
    #endif
    free(p_line);
    
    return TRUE;
}

Bool_e find_filename_from_id(unsigned long id, char** filename)
{
    FILE* p_list_base;
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
            *filename = (char*) malloc((strlen(buf) + 1) * sizeof(char));
            if(*filename == NULL)
            {
                fprintf(stderr, "Error memory allocating.\n\r");
            }
            strcpy(*filename, buf);
            if (fclose(p_list_base) == EOF)
            {
                fprintf(stderr, "Error closing %s.\n\r", LIST_BASE_TEXT_PATH);
                return FALSE;
            }
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

Bool_e display_research_by_text(char* path)
{
    /* statements */
    Text_descriptor_s desc;
    char word[MAX_MEMORY_STRING];
    char* line;
    unsigned int num_occurences;
    char* p_name;
    Bool_e found;
    float max;
    unsigned long hash_code;
    unsigned int i, j;
    Keywords_s keywords;
    FILE* p_indexing_table;
    char* p_line;
    char* new_buffer;
    char* temp_desc;
    char buf[MAX_MEMORY_STRING];
    char string[MAX_MEMORY_STRING];

    Bool_e first;

    /* initalizations */
    first = TRUE;
    init_keywords(&keywords);

    /* instructions */
    clear_console();
    print_plate_console();
    display_centered_text_console("");
    sprintf(string, "Requete : %s", path);
    display_centered_text_console(string);
    display_centered_text_console("");

    /* STEP 1 : Indexing the text in param */
    if (index_text(path, &desc) == FALSE)
    {
        fprintf(stderr, "Error indexing text research by text %s", path);
        return FALSE;
    }

    /*Source : https://stackoverflow.com/questions/17983005/c-how-to-read-a-string-line-by-line */
    /* Read line one by one and add the word/occurence to the tree */
    temp_desc = desc.descriptor_contents; 
    while (desc.descriptor_contents)
    {
        new_buffer = strchr(desc.descriptor_contents, '\n');
        size_t line_len = new_buffer ? (size_t)(new_buffer - desc.descriptor_contents) : strlen(desc.descriptor_contents);
        line = (char*) malloc(line_len + 1);

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

            /* step 1 : memory allocation */
            keywords.keywords = (Keyword_s*) realloc(keywords.keywords, sizeof(Keyword_s) * (keywords.size + 1));
            if (keywords.keywords == NULL)
            {
                fprintf(stderr, "Error re-allocating memory.\n\r");
                return FALSE;
            }

            keywords.keywords[keywords.size].word = (char*) malloc(sizeof(char*) * strlen(word));
            if (keywords.keywords[keywords.size].word == NULL)
            {
                fprintf(stderr, "Error allocating memory.\n\r");
                return FALSE;
            }

            strcpy(keywords.keywords[keywords.size].word, word);
            keywords.keywords[keywords.size].occurences = num_occurences;

            keywords.size++;
        }

        free(line);

        desc.descriptor_contents = new_buffer ? (new_buffer + 1) : NULL; /* Remove the line (the +1 skips the \n) */
    }

    free(temp_desc);

    p_indexing_table = fopen(INDEX_TABLE_TEXT_DESCRIPTOR_PATH, "r");
    if (p_indexing_table == NULL)
    {
        fprintf(stderr, "Error opening %s.\n\r", INDEX_TABLE_TEXT_DESCRIPTOR_PATH);
        return FALSE;
    }

    for (i = 0; i < keywords.size; i++)
    {
        /* step 2 : compute all weights for each keyword */
        keywords.keywords[i].word_weight = (float)keywords.keywords[i].occurences / (float)keywords.keywords[0].occurences;

        if (file_contains_string(p_indexing_table, keywords.keywords[i].word, &p_line) == TRUE)
        {
            while (fgets(buf, sizeof(buf), p_indexing_table) != 0)
            {
                if (buf[0] == '\n')
                {
                    break;
                }

                sscanf(buf, "%lu %u", &hash_code, &num_occurences);

                /* case first text */
                if (keywords.size_scores == 0)
                {
                    keywords.score_texts = realloc(keywords.score_texts, sizeof(Score_text_s) * (keywords.size_scores + 1));
                    if (keywords.score_texts == NULL)
                    {
                        fprintf(stderr, "Error : realloc failed in comparaison_text research by text.\n\r");
                        return FALSE;
                    }

                    keywords.score_texts[0].id = hash_code;
                    keywords.score_texts[0].score = (float)num_occurences * keywords.keywords[i].word_weight;
                    keywords.size_scores++;
                }
                else
                {
                    /* check if the text has already a score */
                    for (j = 0, found = FALSE; j < keywords.size_scores && found == FALSE; j++)
                    {
                        if (hash_code == keywords.score_texts[j].id)
                        {
                            keywords.score_texts[j].score += (float) num_occurences * keywords.keywords[i].word_weight;
                            found = TRUE;
                        }
                    }

                    if (found == FALSE)
                    {
                        keywords.score_texts = realloc(keywords.score_texts, sizeof(Score_text_s) * (keywords.size_scores + 1));
                        if (keywords.score_texts == NULL)
                        { 
                            fprintf(stderr, "Error : realloc failed in comparaison_text research by text.\n\r");
                            if (pclose(p_indexing_table) == EOF)
                            {
                                fprintf(stderr, "Error closing %s.\n\r", INDEX_TABLE_TEXT_DESCRIPTOR_PATH);
                                return FALSE;
                            } 
                            return FALSE;
                        }

                        keywords.score_texts[keywords.size_scores].id = hash_code;
                        keywords.score_texts[keywords.size_scores].score = (float) num_occurences * keywords.keywords[i].word_weight;
                        keywords.size_scores++;
                    }
                }
            }
        }
        free(p_line);
        fseek(p_indexing_table, 0, SEEK_SET);
    }

    if (pclose(p_indexing_table) == EOF)
    {
        fprintf(stderr, "Error closing %s.\n\r", INDEX_TABLE_TEXT_DESCRIPTOR_PATH);
        return FALSE;
    }   

    /* can be optimized but not enough time */
    if(keywords.size_scores > 0)
    {
        while(1)
        {
            max = -1;

            for(i = 0; i < keywords.size_scores; i++)
            {
                if(keywords.score_texts[i].score > max)
                {
                    max = keywords.score_texts[i].score;
                    j = i;
                }
            }

            if(max == -1)
            {
                break;
            }

            if(find_filename_from_id(keywords.score_texts[j].id, &p_name) == FALSE)
            {
                return FALSE;
            }

            if(first == TRUE)
            {
                first = FALSE;
                open_file(TEXT_BASE_PATH, p_name);
            }

            sprintf(word, "%s %.1f", p_name, keywords.score_texts[j].score);

            display_centered_text_console(word);

            keywords.score_texts[j].score = -1;

            free(p_name);
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

    for(i = 0; i < keywords.size; i++)
    {
        free(keywords.keywords[i].word);
    }
    free(keywords.keywords);
    free(keywords.score_texts);

    return TRUE;
}