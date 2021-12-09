/*
Authors:    Constant ROUX,
            Julian TRANI,
            Peter PIRIOU--DEZY,
            Guillaume ROUSSIN,
            Nelson SANCHEZ
            
Date:       29/11/2021
*/

#ifndef CONFIG_TREE_H
#define CONFIG_TREE_H

typedef struct node
{
    void* data;
    struct node* branch[];
} Node_s;

#endif