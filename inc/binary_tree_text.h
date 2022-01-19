#ifndef BINARY_TREE_TEXT_H
#define BINARY_TREE_TEXT_H

#include "toolbox.h"
#include "word.h"

typedef struct tree
{
    Word_s* root; 
    struct tree* p_left;
    struct tree* p_right;
} Word_Leaf_s;

typedef Word_Leaf_s* Word_Tree_s;

Word_Tree_s init_word_tree();
Bool_e is_empty_word_tree(Word_Tree_s word_tree);
Bool_e add_occurence_to_tree(Word_Tree_s* p_word_tree, char* word, Word_occurence_s occurence);
void add_word_to_tree(Word_Tree_s *tree, Word_s *word_object) ;
void find_word_in_tree(Word_Tree_s* p_word_tree, char* word, Word_s** found_item);
Bool_e save_dictionary_to_file(Word_Tree_s p_word_tree, FILE *p_stream);

#endif