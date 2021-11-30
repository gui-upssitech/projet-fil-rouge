#ifndef DISPLAY_H
#define DISPLAY_H

/* useful constants for displaying the console */
#define WALL "|"
#define SPACE " "
#define PLATE "-"
#define CORNER "+"
#define MAX_CHAR_PER_LINE 60

void display_text_console(char* p_text);
void print_blank_console(unsigned int blank_size);
void print_plate_console();

#endif