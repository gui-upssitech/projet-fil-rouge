/*
Authors:    Constant ROUX,
            Julian TRANI,
            Peter PIRIOU--DEZY,
            Guillaume ROUSSIN        
            
Date:       29/11/2021
*/

#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include "toolbox.h"
#include "comparaison_generic.h"

/**
 * @brief A struct which represents a leaf of the binary search tree.
 * 
 */
typedef struct leaf
{
    Result_s result; /**< The result (IMAGE or AUDIO). */
    struct leaf* p_left; /**< The left leaf pointer (IMAGE or AUDIO). */ 
    struct leaf* p_right; /**< The right leaf pointer (IMAGE or AUDIO). */
    /*@}*/
} Leaf_s;

/**
 * @brief A type to represent a tree, the first leaf of binary search tree. 
 */
typedef Leaf_s* Binary_search_tree_p; 

/**
 * @brief Display all results in a binary search tree in descending order (right then left) of confidence.
 * 
 * @param binary_search_tree The tree (init and fill) for which we want to display results. 
 * @param data_type The data type of each result (IMAGE or AUDIO).
 * @return Bool_e TRUE if the diplay succeed, FALSE else.
 */
Bool_e display_binary_search_tree(Binary_search_tree_p binary_search_tree, Descriptor_e data_type);

/**
 * @brief Init a binary search tree by setting the first node to NULL.
 * 
 * @return Binary_search_tree_p Return a null pointer of a Leaf_s type.
 */
Binary_search_tree_p init_binary_search_tree();

/**
 * @brief Check if a binary search tree is empty.
 * 
 * @param p_binary_search_tree The binary search tree for which we want to check if it is empty.
 * @return Bool_e TRUE if the binary search is empty, FALSE else.
 */
Bool_e is_empty_binary_search_tree(Binary_search_tree_p p_binary_search_tree);

/**
 * @brief Add a result in a binary search tree. Left if the confidence of the result is lower than the current node,
 * right else.
 * 
 * @param p_binary_search_tree A pointer of the binary search tree for wich we want to add a result.
 * @param result The result to add.
 */
void add_node_binary_search_tree_image(Binary_search_tree_p* p_binary_search_tree, Result_s result);

/**
 * @brief Add a result in a binary search tree. Left if the confidence of the result is lower than the current node,
 * right else.
 * 
 * @param p_binary_search_tree A pointer of the binary search tree for wich we want to add a result.
 * @param result The result to add.
 * @param duration The time code of the result.
 */
void add_node_binary_search_tree_audio(Binary_search_tree_p* p_binary_search_tree, Result_s result, int duration);

/**
 * @brief Get the max confidence in the tree.
 * 
 * @param p_result The result of the search.
 * @param binary_search_tree The tree in which to search the max value.
 */
void get_max_tree(Result_s* p_result, Binary_search_tree_p binary_search_tree);

/**
 * @brief Get the max confidence in the audio tree.
 * 
 * @param p_result The result of the search.
 * @param binary_search_tree  The tree in which to search the max value.
 */
void get_max_confidence_audio_tree(Result_s* p_result, Binary_search_tree_p binary_search_tree);

#endif