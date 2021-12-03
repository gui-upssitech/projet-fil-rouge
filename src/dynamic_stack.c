/*
Authors:    Constant ROUX,
            Julian TRANI,
            Peter PIRIOU--DEZY,
            Guillaume ROUSSIN,
            Nelson SANCHEZ
            
Date:       29/11/2021
*/

#include <stdio.h>
#include <stdlib.h>

#include "../inc/dynamic_stack.h"
#include "../inc/toolbox.h"

Dynamic_stack_p init_dynamic_stack()
{
    /* instructions */
    return NULL;
}

Bool_e is_empty_dynamic_stack(Dynamic_stack_p p_dynamic_stack)
{
    /* instructions */
    return (p_dynamic_stack == NULL) ? TRUE : FALSE;
}

Dynamic_stack_p add_unit_dynamic_stack(Dynamic_stack_p p_dynamic_stack, Unit_u unit)
{
    /* statements */
    Node_s* p_node;

    /* instructions */
    p_node = malloc(sizeof(Node_s));
    if(p_node == NULL)
    {
        fprintf(stderr, "Error memory allocation.\n\r");
    }
    else
    {
        p_node->next_node = p_dynamic_stack;
        affect_unit(&(p_node->element), unit);

        p_dynamic_stack = p_node;
    }
    return p_dynamic_stack;
}

Dynamic_stack_p remove_unit_dynamic_stack(Dynamic_stack_p p_dynamic_stack, Unit_u* unit)
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
        affect_unit(unit, p_node->element);
        p_dynamic_stack = p_node->next_node;
        free(p_node);
    }
    return p_dynamic_stack;
}