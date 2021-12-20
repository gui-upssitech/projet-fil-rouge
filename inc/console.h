/*
Authors:    Constant ROUX,
            Julian TRANI,
            Peter PIRIOU--DEZY,
            Guillaume ROUSSIN,
            Nelson SANCHEZ
            
Date:       29/11/2021
*/

#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>

#include "comparaison_image.h"
#include "toolbox.h"
#include "admin.h"

/* useful constants for displaying the console */
#define WALL "|"
#define SPACE " "
#define PLATE "-"
#define CORNER "+"
#define MAX_CHAR_PER_LINE 60

void display_centered_text_console(char* p_text);
void print_blank_console(unsigned int blank_size);
char get_char_menu(char num_choices);
void print_plate_console();
void display_login_menu();
Bool_e display_new_pwd_menu(Bool_e first_password);
void display_main_menu();
void display_user_menu();
void display_admin_menu();
void display_about_menu();
void display_text_research_menu();
void display_image_research_menu();
void display_audio_research_menu();
Bool_e display_image_color_research_menu();
void display_image_result_menu(Binary_search_tree_p confidence_tree, char* path);

#endif