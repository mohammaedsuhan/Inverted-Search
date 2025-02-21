#ifndef INVERTED_INDEX_H
#define INVERTED_INDEX_H 

/* Standard Libraries Inclusion */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


/* MACRO definitions */
#define SUCCESS 0
#define FAILURE -1
#define NOELEMENT -2
#define EMPTYLIST -3
#define REPEATED -4
#define FILE_EMPTY -5
#define NOT_PRESENT -6

#define SIZE 28
#define BUFF_SIZE 255
#define NAMELENGTH 50

/* Typedefs definition */
typedef struct sub_node
{
	char f_name [NAMELENGTH];
	int w_count;
	struct sub_node *link;
} sub_node_t;

typedef struct node
{
	char word [NAMELENGTH];
	struct node *link;
	sub_node_t *sub_link;
	int f_count;
} main_node_t;

typedef struct file_node
{
    char f_name [NAMELENGTH];
    struct file_node *link;
} file_node_t;

/* Function Declarations for all the Operations */
int command_handler (char* []);

/* File Validation */
void validate_n_store_filenames (file_node_t**, char* []);
int IsFileValid (char*);
int IsFileDuplicate (char*, file_node_t**);
int store_filenames_to_list (char*, file_node_t**);
int insert_at_last_file (file_node_t**, char*);

/* Create Database */
int create_DB (file_node_t*, main_node_t**);
void read_datafile (main_node_t**, char*);
int get_key (char);
int check_word (char*, main_node_t*);
int insert_at_last_main (main_node_t**, char*, char*);
sub_node_t* create_sub_node (char*);
int check_file (char*, char*, main_node_t*);
int update_link_table (main_node_t**, char*, char*);
int update_word_count (main_node_t**, char*, char*);

/* Display Database */
int display_DB (main_node_t**);
void display_words (main_node_t*, int);
void display_files (sub_node_t*);

/* Search Database */
int search_DB (main_node_t**, char*);

/* Update Database */
int update_DB (file_node_t**, main_node_t**, char*);

/* Save Database */
int save_DB (main_node_t**, char*);
int check_name (char*);

#endif
