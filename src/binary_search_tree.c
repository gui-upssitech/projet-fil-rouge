#include <stdio.h>
#include <stdlib.h>

#include "binary_search_tree.h"
#include "console.h"

Bool_e display_binary_search_tree(Binary_search_tree_p binary_search_tree, Descriptor_e data_type)
{
    /* statements */
    char buf[MAX_CHAR_PER_LINE - 4 + MAX_MEMORY_STRING];

    /* instructions */
    if (is_empty_binary_search_tree(binary_search_tree) == TRUE)
    {
        fprintf(stderr, "Error binary search tree is empty.\n\r");
        return FALSE;
    }

    switch (data_type)
    {
    case IMAGE:
        if (binary_search_tree->p_right != NULL)
        {
            display_binary_search_tree(binary_search_tree->p_right, data_type);
        }
        sprintf(buf, "%s [%3.2f %%]", binary_search_tree->result.name, binary_search_tree->result.confidence);
        display_centered_text_console(buf);
        if (binary_search_tree->p_left != NULL)
        {
            display_binary_search_tree(binary_search_tree->p_left, data_type);
        }
        break;

    case AUDIO:
        if (binary_search_tree->p_left != NULL)
        {
            display_binary_search_tree(binary_search_tree->p_left, data_type);
        }
        sprintf(buf, "%3.2f %% at %ds", binary_search_tree->result.confidence, binary_search_tree->result.time_code);
        display_centered_text_console(buf);
        if (binary_search_tree->p_right != NULL)
        {
            display_binary_search_tree(binary_search_tree->p_right, data_type);
        }
        break;

    default:
        break;
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

void add_node_binary_search_tree_image(Binary_search_tree_p *p_binary_search_tree, Result_s result)
{
    /* statements */
    Leaf_s *p_leaf;

    /* instructions */
    p_leaf = (Leaf_s *)malloc(sizeof(Leaf_s));
    if (p_leaf == NULL)
    {
        printf("Error memory allocation.\n\r");
        return;
    }

    if (is_empty_binary_search_tree(*p_binary_search_tree))
    {
        p_leaf->p_left = NULL;
        p_leaf->p_right = NULL;
        p_leaf->result = result;
        *p_binary_search_tree = p_leaf;
    }
    else
    {
        p_leaf = *p_binary_search_tree;
        while (1)
        {
            if (result.confidence < p_leaf->result.confidence)
            {
                if (p_leaf->p_left == NULL)
                {
                    Leaf_s *p_buf;
                    p_buf = (Leaf_s *)malloc(sizeof(Leaf_s));
                    if (p_buf == NULL)
                    {
                        printf("Error memory allocation.\n\r");
                        return;
                    }
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
            else if (result.confidence > p_leaf->result.confidence)
            {
                if (p_leaf->p_right == NULL)
                {
                    Leaf_s *p_buf;
                    p_buf = (Leaf_s *)malloc(sizeof(Leaf_s));
                    if (p_buf == NULL)
                    {
                        printf("Error memory allocation.\n\r"); // TO DO
                        return;
                    }
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
            else
            {
                break;
            }
        }
    }
}

void add_node_binary_search_tree_audio(Binary_search_tree_p *p_binary_search_tree, Result_s result, int duration)
{
    /* statements */
    Leaf_s *p_leaf;

    /* instructions */
    p_leaf = (Leaf_s *)malloc(sizeof(Leaf_s));
    if (p_leaf == NULL)
    {
        printf("Error memory allocation.\n\r");
        return;
    }

    if (is_empty_binary_search_tree(*p_binary_search_tree))
    {
        p_leaf->p_left = NULL;
        p_leaf->p_right = NULL;
        p_leaf->result = result;
        *p_binary_search_tree = p_leaf;
    }
    else
    {
        p_leaf = *p_binary_search_tree;
        while (1)
        {
            if (result.time_code > p_leaf->result.time_code + duration)
            {
                if (p_leaf->p_right == NULL)
                {
                    Leaf_s *p_buf;
                    p_buf = (Leaf_s *)malloc(sizeof(Leaf_s));
                    if (p_buf == NULL)
                    {
                        printf("Error memory allocation.\n\r"); // TO DO
                        return;
                    }
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
            else
            {
                break;
            }
        }
    }
}

void get_max_tree(Result_s* p_result, Binary_search_tree_p binary_search_tree)
{
    /* instructions */
    if (is_empty_binary_search_tree(binary_search_tree->p_right) == FALSE)
    {
        get_max_tree(p_result, binary_search_tree->p_right); 
    }
    else
    {
        *p_result = binary_search_tree->result;
    }
}