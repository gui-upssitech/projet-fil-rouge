/*
Authors:    Constant ROUX,
            Julian TRANI,
            Peter PIRIOU--DEZY,
            Guillaume ROUSSIN            
            
Date:       29/11/2021
*/

#ifndef TOOLBOX_H
#define TOOLBOX_H

#include <stdio.h>

/* useful macros */
#define PWRTWO(x) (1 << (x))
#define ABS_INT(x) (((x) < 0) ? (-(x)) : (x))

/* const values for file */
#define TEXT_EXTENSION ".txt"
#define XML_EXTENSION ".xml"
#define BIN_EXTENSION ".bin"

/* useful memory constants */
#define MAX_MEMORY_STRING 1024

/* useful char constants */
#define ESCAPE_KEY 27
#define ENTER_KEY 10

/* classical boolean type */
typedef enum {FALSE, TRUE} Bool_e;

/**
 * @brief Know if the path file is corresponding to a regular file.
 * 
 * @param path The path file.
 * @return Bool_e TRUE if the file is regular, FALSE else.
 */
Bool_e is_regular_file(const char *path);

/**
 * @brief Know if the file is corresponding to a specific extension file.
 * 
 * @param path The path file.
 * @return Bool_e TRUE if the file is the specific extension, FALSE else.
 */
Bool_e is_extension_file(const char* path, char* extension);

/**
 * @brief Read a path with Enter key validation or Escape key abandonment.
 * 
 * @param path A pointer to the first case adress of the path string.
 * @param code A code status (0 if Enter key validation, -1 if Escape key abandonment)
 * @return Bool_e TRUE if succeed, FALSE else.
 */
Bool_e read_string(char** path, int* code);

/**
 * @brief Shift bits of a b-times to the left if b is positive, to the right else.
 * 
 * @param a The value to shift on 8 bits.
 * @param b The shift size.
 * @return unsigned short The shifted value on 16 bits.
 */
unsigned short shift(unsigned char a, int b);

/**
 * @brief Read an integer from stdin.
 * 
 * @param p_value A integer pointer which will contains the read value.
 * @return Bool_e TRUE if the user puts an integer in stdin, FALSE else.
 */
Bool_e read_integer(long* p_value);

/**
 * @brief Transform a string to an unique unsigned long.
 * 
 * @param p_string The string to hash.
 * @return unsigned long The hashed string.
 */
unsigned long hash(char* p_string);

/**
 * @brief Get the array size from pointer char
 * 
 * @param p_array The char array for which we want the size.
 * @return unsigned int The size of the array.
 */
unsigned int get_array_size_from_pointer(const char* p_array);

/**
 * @brief Flush the stdin buffer.
 * 
 */
void fflush_stdin(void);

/**
 * @brief Get a char in stdin without echo and enter-key validation.
 * 
 * @return char The read char from stdin.
 */
char getch(void);

/**
 * @brief Know if a file contains a specific string.
 * 
 * @param p_file The file descriptor opened.
 * @param p_str The string that we are looking for.
 * @param p_line The file line which contains p_str.
 * @return Bool_e TRUE if the file contains the substring, FALSE else.
 */
Bool_e file_contains_substring(FILE* p_file, char* p_str, char** p_line);

/**
 * @brief Concat two strings from char pointers.
 * 
 * @param str1 The first string represented by a char pointer (left).
 * @param str2 The second string represented by a char pointer (right).
 * @return char* The new line
 */
char* str_concat(char* str1, char* str2);

/**
 * @brief Get the size of a file in bytes.
 * 
 * @param p_file The opened file descriptor.
 * @return unsigned int The number of bytes in p_file.
 */
unsigned int get_bytes_size_file(FILE* p_file);

#endif