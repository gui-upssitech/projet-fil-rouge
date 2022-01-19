/*
Authors:    Constant ROUX,
            Julian TRANI,
            Peter PIRIOU--DEZY,
            Guillaume ROUSSIN
                    
Date:       29/11/2021
*/

#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>

#include "comparaison_audio.h"
#include "comparaison_image.h"
#include "toolbox.h"
#include "admin.h"

/* useful constants for displaying the console */
#define WALL "|"
#define SPACE " "
#define PLATE "-"
#define CORNER "+"
#define MAX_CHAR_PER_LINE 60

/**
 * @brief Clear the console.
 * 
 */
void clear_console();

/**
 * @brief Display a centered text depending of macro-parameters (MAX_CHAR_PER_LINE, WALL).
 * 
 * @param p_text The text to display.
 */
void display_centered_text_console(const char *p_text);

/**
 * @brief Print blank_size time a SPACE in console. 
 * 
 * @param blank_size The number of SPACE.
 */
void print_blank_console(unsigned int blank_size);

/**
 * @brief Read the choice of user.
 * 
 * @param num_choices The number of possible choices.
 * @return char 
 */
char get_char_menu(char num_choices);

/**
 * @brief Display a plate on console depending of macro-parameters (MAX_CHAR_PER_LINE, CORNER, PLATE).
 * 
 */
void print_plate_console();

/**
 * @brief Display the login menu.
 * 
 */
void display_login_menu();

/**
 * @brief Display the new password menu.
 * 
 * @param first_password A boolean in case of first connection (no existing password).
 * @return Bool_e TRUE if new password is saved, FALSE else.
 */
Bool_e display_new_pwd_menu(Bool_e first_password);

/**
 * @brief Display the main menu.
 * 
 */
void display_main_menu();

/**
 * @brief Display the user menu.
 * 
 */
void display_user_menu();

/**
 * @brief Display the admin menu.
 * 
 */
void display_admin_menu();

/**
 * @brief Display the about menu.
 * 
 */
void display_about_menu();

/**
 * @brief Display the text research menu.
 * 
 */
void display_text_research_menu();

/**
 * @brief Display the image research menu.
 * 
 */
void display_image_research_menu();

/**
 * @brief Display the image by path research menu.
 * 
 * @param colored Boolean variable to indicate if the menu image is for colored images or gray images.
 * @return Bool_e TRUE if the research succeed, FALSE else.
 */
Bool_e display_image_by_path_research_menu(Bool_e colored);

/**
 * @brief Display image result menu.
 * 
 * @param confidence_tree The tree of results.
 * @param path The path of the search image by user.
 * @param colored Boolean variable to indicate if the menu is for a colored or gray image.
 */
void display_image_result_menu(Binary_search_tree_p confidence_tree, char *path, Bool_e colored);

/**
 * @brief Display audio by path research menu.
 * 
 * @return Bool_e TRUE if search succeed, FALSE else.
 */
Bool_e display_audio_by_path_research_menu();

/**
 * @brief Display audio result menu.
 * 
 * @param time_code_forest A pointer representing an array of trees containing time codes.
 * @param size The size of time_code_forest.
 * @param path The path of the search file by user.
 */
void display_audio_result_menu(Binary_search_tree_p *time_code_forest, unsigned int size, char *path);

/**
 * @brief Display indexing admin menu.
 * 
 */
void display_indexation_admin_menu();

/**
 * @brief Display the menu of research by keyword
 * 
 * @return Bool_e 
 */
Bool_e display_text_research_by_keyword_menu();

/**
 * @brief Display the menu of research by text
 * 
 * @return Bool_e 
 */
Bool_e display_text_research_by_text_menu();

#endif