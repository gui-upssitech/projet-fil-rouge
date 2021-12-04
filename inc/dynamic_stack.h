/*
Authors:    Constant ROUX,
            Julian TRANI,
            Peter PIRIOU--DEZY,
            Guillaume ROUSSIN,
            Nelson SANCHEZ
            
Date:       29/11/2021
*/

#ifndef DYNAMIC_STACK_H
#define DYNAMIC_STACK_H

#include "unit.h"
#include "toolbox.h"

/* TYPES */
typedef struct node {
    Unit_u element;
    struct node* next_node;
} Node_s;

typedef Node_s* Dynamic_stack_p;

/* FUNCTIONS */
Dynamic_stack_p init_dynamic_stack();
Bool_e is_empty_dynamic_stack(Dynamic_stack_p p_dynamic_stack);
Dynamic_stack_p add_unit_dynamic_stack(Dynamic_stack_p p_dynamic_stack, Unit_u unit, Descriptor_e descriptor_type);
Dynamic_stack_p remove_unit_dynamic_stack(Dynamic_stack_p p_dynamic_stack, Unit_u* unit, Descriptor_e descriptor_type);

#endif