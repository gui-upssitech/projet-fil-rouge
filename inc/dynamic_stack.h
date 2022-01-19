/*
Authors:    Constant ROUX,
            Julian TRANI,
            Peter PIRIOU--DEZY,
            Guillaume ROUSSIN
                        
Date:       29/11/2021
*/

#ifndef DYNAMIC_STACK_H
#define DYNAMIC_STACK_H

#include <stdio.h>
#include <stdlib.h>

#include "unit.h"
#include "toolbox.h"
#include "indexation_generic.h"

/**
 * @brief A node struct of the dynamic stack.
 * 
 */
typedef struct node 
{
    Unit_u element; /**< The element in the node. */
    struct node* next_node; /**< The pointer to the next node. */
} Node_s;

/**
 * @brief The type dynamic stack declared as the pointer of a node.
 * 
 */
typedef Node_s* Dynamic_stack_p;

/**
 * @brief Init the dynamic stack.
 * 
 * @return Dynamic_stack_p The dynamic stack initialized.
 */
Dynamic_stack_p init_dynamic_stack(void);

/**
 * @brief The state of the dynamic stack.
 * 
 * @param p_dynamic_stack The dynamic stack to check. 
 * @return Bool_e TRUE if dynamic_stack is empty, FALSE else.
 */
Bool_e is_empty_dynamic_stack(Dynamic_stack_p p_dynamic_stack);

/**
 * @brief Add new unit in the dynamic stack.
 * 
 * @param p_dynamic_stack The dynamic stack in which to add the unit.
 * @param unit The unit to add.
 * @param descriptor_type The type of unit.
 * @return Dynamic_stack_p The new dynamic stack with the added unit.
 */
Dynamic_stack_p add_unit_dynamic_stack(Dynamic_stack_p p_dynamic_stack, Unit_u unit, Descriptor_e descriptor_type);

/**
 * @brief Remove unit of the dynamic stack.
 * 
 * @param p_dynamic_stack The dynamic stack in which to remove the unit.
 * @param unit The removed unit.
 * @param descriptor_type The type unit.
 * @return Dynamic_stack_p The new dynamic stack with the removed unit.
 */
Dynamic_stack_p remove_unit_dynamic_stack(Dynamic_stack_p p_dynamic_stack, Unit_u* unit, Descriptor_e descriptor_type);

#endif