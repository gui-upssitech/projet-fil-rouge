#include <stdio.h>
#include <stdlib.h>

#include "binary_search_tree.h"

Bool_e display_binary_search_tree(Binary_search_tree_p binary_search_tree, Descriptor_e data_type)
{
    if(is_empty_binary_search_tree(binary_search_tree) == TRUE)
    {
        fprintf(stderr, "Error binary search tree is empty.\n\r");
        return FALSE;
    }

    if(binary_search_tree->p_right != NULL)
    {
        display_binary_search_tree(binary_search_tree->p_right, data_type);
    }

    switch(data_type)
    {
        case IMAGE:
            printf("%s : %3.2f %%\n\r", binary_search_tree->result.name, binary_search_tree->result.confidence);
            break;
        
        case AUDIO:
            printf("%s : %3.2f %% at %d\n\r", binary_search_tree->result.name, binary_search_tree->result.confidence, binary_search_tree->result.time_code);
            break;
        
        default:
            break;
    }

    if(binary_search_tree->p_left != NULL)
    {
        display_binary_search_tree(binary_search_tree->p_left, data_type);
    }

    return TRUE;
}

Binary_search_tree_p init_binary_search_tree()
{
    /* instructions */
    return NULL;
}

Bool_e is_empty_binary_search_tree(Binary_search_tree_p p_binary_search_tree)
{
    /* instructions */
    return (p_binary_search_tree == NULL) ? TRUE : FALSE;
}

void add_node_binary_search_tree(Binary_search_tree_p* p_binary_search_tree, Result_s result)
{
    /* declarations */
    Leaf_s* p_leaf;

    /* instructions */
    p_leaf = (Leaf_s*) malloc(sizeof(Leaf_s));
    if(p_leaf == NULL)
    {
        printf("Error memory allocation.\n\r");
        return;
    }

    if(is_empty_binary_search_tree(*p_binary_search_tree))
    {
        p_leaf->p_left = NULL;
        p_leaf->p_right = NULL;
        p_leaf->result = result;
        *p_binary_search_tree = p_leaf;
    }
    else
    {
        p_leaf = *p_binary_search_tree;
        while(1) 
        {
            if(result.confidence < p_leaf->result.confidence)
            {   
                if(p_leaf->p_left == NULL)
                {
                    Leaf_s* p_buf;
                    p_buf = (Leaf_s*) malloc(sizeof(Leaf_s));
                    p_buf->p_right = NULL;
                    p_buf->p_left = NULL;
                    p_buf->result = result;
                    p_leaf->p_left = p_buf;
                    break;
                }
                else
                {
                    p_leaf = p_leaf->p_left;
                }
            }
            else if(result.confidence > p_leaf->result.confidence)
            {
               if(p_leaf->p_right == NULL)
                {
                    Leaf_s* p_buf;
                    p_buf = (Leaf_s*) malloc(sizeof(Leaf_s));
                    p_buf->p_right = NULL;
                    p_buf->p_left = NULL;
                    p_buf->result = result;
                    p_leaf->p_right = p_buf;
                    break;
                }
                else
                {
                    p_leaf = p_leaf->p_right;
                }
            }
        }
    }   
}

