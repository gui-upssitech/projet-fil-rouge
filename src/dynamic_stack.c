/*
Authors:    Constant ROUX,
            Julian TRANI,
            Peter PIRIOU--DEZY,
            Guillaume ROUSSIN,
            Nelson SANCHEZ
            
Date:       29/11/2021
*/

#include "dynamic_stack.h"

Dynamic_stack_p init_dynamic_stack(void)
{
    /* instructions */
    return NULL;
}

Bool_e is_empty_dynamic_stack(Dynamic_stack_p p_dynamic_stack)
{
    /* instructions */
    return (p_dynamic_stack == NULL) ? TRUE : FALSE;
}

Dynamic_stack_p add_unit_dynamic_stack(Dynamic_stack_p p_dynamic_stack, Unit_u unit, Descriptor_e descriptor_type)
{
    /* statements */
    Node_s* p_node;

    /* instructions */
    int value = sizeof(Unit_u);
    int size = sizeof(Node_s);
    p_node = (Node_s*) malloc(size * 2);
    if(p_node == NULL)
    {
        fprintf(stderr, "Error memory allocation.\n\r");
    }
    else
    {
        p_node->next_node = p_dynamic_stack;
        affect_unit(&(p_node->element), unit, descriptor_type);

        p_dynamic_stack = p_node;
    }
    return p_dynamic_stack;
}

Dynamic_stack_p remove_unit_dynamic_stack(Dynamic_stack_p p_dynamic_stack, Unit_u* unit, Descriptor_e descriptor_type)
{
    /* statements */
    Node_s* p_node;

    /* instructions */
    if(is_empty_dynamic_stack(p_dynamic_stack) == TRUE)
    {
        printf("The dynamic stack is empty.\n\r");
    }
    else
    {   
        p_node = p_dynamic_stack;
        affect_unit(unit, p_node->element, descriptor_type);
        p_dynamic_stack = p_node->next_node;
        free(p_node);
    }
    return p_dynamic_stack;
}