#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "binary_tree_text.h"
#include "configurations.h"

Word_Tree_s init_word_tree()
{
    /* instructions */
    return NULL;
}

Bool_e is_empty_word_tree(Word_Tree_s word_tree)
{
    return (word_tree == NULL) ? TRUE : FALSE;
}

Bool_e add_occurence_to_tree(Word_Tree_s *p_word_tree, char *word, Word_occurence_s occurence)
{
    Word_s *word_object;

    /* Step 1 : try to find word */
    word_object = NULL;
    find_word_in_tree(p_word_tree, word, &word_object);

    /* Step 2 : If word not found, create word and add to tree */
    if (word_object == NULL)
    {
        /* Create cell */
        init_word(word, &word_object);
        add_word_to_tree(p_word_tree, word_object);
    }

    /* Step 3 : insert sort the occurence */
    add_occurence(&word_object, occurence);

    return TRUE;
}

void add_word_to_tree(Word_Tree_s *tree, Word_s *word_object)
{
    /* Step 1 : checking if the tree is empty so we add the element */
    if (is_empty_word_tree(*tree) == TRUE)
    {
        Word_Leaf_s* leaf = (Word_Leaf_s *)malloc(sizeof(Word_Leaf_s));
        if(leaf == NULL)
        {
            fprintf(stderr, "Error leaf memory allocation in text binary tree.\n\r");
            return;
        }

        leaf->p_left = NULL;
        leaf->p_right = NULL;
        leaf->root = word_object;

        *tree = leaf;
    }
    else
    {
        /* Step 2 : checking wich size choose to add the word_object*/
        if (strcmp((*tree)->root->word_name, word_object->word_name) < 0)
        {
            add_word_to_tree(&((*tree)->p_right), word_object);
        }
        else if (strcmp((*tree)->root->word_name, word_object->word_name) > 0)
        {
            add_word_to_tree(&((*tree)->p_left), word_object);
        }
        else
        {
            fprintf(stderr, "Error: '%s' already exists in tree but didn't find in find_word_in_tree\n", word_object->word_name);
            return;
        }
    }
}

void find_word_in_tree(Word_Tree_s* p_word_tree, char *word, Word_s **found_item)
{
    if(is_empty_word_tree(*p_word_tree) == TRUE)
    {
        *found_item = NULL;
    }
    else
    {
        /* recursive checking */
        /* If the value is less than the root */
        if (strcmp((*p_word_tree)->root->word_name, word) > 0)
        {
            find_word_in_tree(&((*p_word_tree)->p_left), word, found_item);
        }
        else if (strcmp((*p_word_tree)->root->word_name, word) < 0)
        {
            find_word_in_tree(&((*p_word_tree)->p_right), word, found_item);
        }
        else if (strcmp((*p_word_tree)->root->word_name, word) == 0)
        {
            *found_item = (*p_word_tree)->root;
        }
    }
}

Bool_e save_dictionary_to_file(Word_Tree_s p_word_tree, FILE *p_stream)
{
    if (p_word_tree != NULL)
    {
        save_dictionary_to_file(p_word_tree->p_left, p_stream);

        
        char* word_desc = (char *) malloc(MAX_MEMORY_STRING * sizeof(char));
        if(word_desc == NULL)
        {
            fprintf(stderr, "Error allocating memory to convert word to string.\n\r");
            return FALSE;
        }
        word_to_string(*(p_word_tree->root), &word_desc);

        if(fprintf(p_stream, "%s\n\n", word_desc) == EOF)
        {
            fprintf(stderr, "Error writing to file.\n\r");
            return FALSE;
        }

        free(word_desc);

        save_dictionary_to_file(p_word_tree->p_right, p_stream);

        free(p_word_tree->root->t_occurences);
        free(p_word_tree->root->word_name);
        free(p_word_tree->root);
        free(p_word_tree);
    }

    return TRUE;
}