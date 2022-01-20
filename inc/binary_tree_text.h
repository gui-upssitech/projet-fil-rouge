/*
Authors:    Constant ROUX,
            Julian TRANI,
            Peter PIRIOU--DEZY,
            Guillaume ROUSSIN        
            
Date:       29/11/2021
*/

#ifndef BINARY_TREE_TEXT_H
#define BINARY_TREE_TEXT_H

#include "toolbox.h"
#include "word.h"

/**
 * @brief 
 * 
 */
typedef struct tree
{
    Word_s* root; 
    struct tree* p_left;
    struct tree* p_right;
} Word_Leaf_s;

/**
 * @brief 
 * 
 */
typedef Word_Leaf_s* Word_Tree_s;

/**
 * @brief 
 * 
 * @return Word_Tree_s 
 */
Word_Tree_s init_word_tree();

/**
 * @brief 
 * 
 * @param word_tree 
 * @return Bool_e 
 */
Bool_e is_empty_word_tree(Word_Tree_s word_tree);

/**
 * @brief 
 * 
 * @param p_word_tree 
 * @param word 
 * @param occurence 
 * @return Bool_e 
 */
Bool_e add_occurence_to_tree(Word_Tree_s* p_word_tree, char* word, Word_occurence_s occurence);

/**
 * @brief 
 * 
 * @param tree 
 * @param word_object 
 */
void add_word_to_tree(Word_Tree_s *tree, Word_s *word_object);

/**
 * @brief 
 * 
 * @param p_word_tree 
 * @param word 
 * @param found_item 
 */
void find_word_in_tree(Word_Tree_s* p_word_tree, char* word, Word_s** found_item);

/**
 * @brief 
 * 
 * @param p_word_tree 
 * @param p_stream 
 * @return Bool_e 
 */
Bool_e save_dictionary_to_file(Word_Tree_s p_word_tree, FILE *p_stream);

#endif