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
 * @brief A struct which represents a leaf of the text binary tree.
 * 
 */
typedef struct tree
{
    Word_s* root; /**< The word in the leaf. */
    struct tree* p_left; /**< The pointer to left leaf. */
    struct tree* p_right; /** The pointer to the right leaf. */
} Word_Leaf_s;

/**
 * @brief A pointer to the first leaf, which represents the root of the tree.
 * 
 */
typedef Word_Leaf_s* Word_Tree_s;

/**
 * @brief Init the tree with NULL.
 * 
 * @return Word_Tree_s The tree initialized.
 */
Word_Tree_s init_word_tree();

/**
 * @brief 
 * 
 * @param word_tree The tree to check.
 * @return Bool_e TRUE if the tree is empty, FALSE else.
 */
Bool_e is_empty_word_tree(Word_Tree_s word_tree);

/**
 * @brief Add an occurence in the text tree.
 * 
 * @param p_word_tree The tree in which to add a new word.
 * @param word The word in which to add the occurence.
 * @param occurence The occurence struct to add corresponding to the word.
 * @return Bool_e TRUE if succeed, FALSE else.
 */
Bool_e add_occurence_to_tree(Word_Tree_s* p_word_tree, char* word, Word_occurence_s occurence);

/**
 * @brief Add word to the tree.
 * 
 * @param tree A pointer to the tree in which to add the new word.
 * @param word_object The word to add.
 */
void add_word_to_tree(Word_Tree_s *tree, Word_s *word_object);

/**
 * @brief Find a word in the tree.
 * 
 * @param p_word_tree A pointer to the tree in which to search the word.
 * @param word The word to find.
 * @param found_item The word found or NULL if not found.
 */
void find_word_in_tree(Word_Tree_s* p_word_tree, char* word, Word_s** found_item);

/**
 * @brief Save the dictionnary to the indexing table file.
 * 
 * @param p_word_tree The three containing all words with occurences found during indexing.
 * @param p_stream The file where to save the dictionnary.
 * @return Bool_e TRUE if saving succeed, FALSE else.
 */
Bool_e save_dictionary_to_file(Word_Tree_s p_word_tree, FILE *p_stream);

#endif