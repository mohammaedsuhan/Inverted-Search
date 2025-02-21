#include "inverted_index.h"

/* To Insert a File Node at the Last in the File Sub-List
 * Input: Head pointer of File List and given File Name
 * Output: Updated File List
 * Return Value: SUCCESS or FAILURE
 */

int insert_at_last_file (file_node_t** head, char* f_name)
{
	file_node_t* new = (file_node_t*) malloc (sizeof (file_node_t));	//Dynamic Memory allocation for adding the new File name into the File List.
	if (new == NULL)		//Error Handling.
		return FAILURE;

	strncpy (new->f_name, f_name, (strlen (f_name) + 1));			//Copy the File name into the New node Data.
	new->link = NULL;		//Update the New node Link as NULL.

	if (*head == NULL)		//If the File List is empty, make the New node as the Head of the File List.
	{
		*head = new;
		return SUCCESS;
	}

	file_node_t* temp = *head;
	while (temp->link != NULL)	//Traverse to insert the New node at the end of List.
	{
		temp = temp->link;	//Update the 'temp' to point to the Next node.
	}

	temp->link = new;		//Update the Last node pointer to point to the New node.

	return SUCCESS;
}

/* To Insert a Word Node at the Last in the Main List
 * Input: Head pointer of the Word List
 * Output: Updated Word List
 * Return Value: SUCCESS or FAILURE
 */

int insert_at_last_main (main_node_t** head, char* word, char* f_name)
{
	main_node_t* new = (main_node_t*) malloc (sizeof (main_node_t));	//Dynamic Memory allocation for adding the new Word into the Word List.
	if (new == NULL)		//Error Handling.
		return FAILURE;

	strncpy (new->word, word, (strlen (word) + 1));				//Copy the Word into the New node Data.
	new->link = NULL;		//Update the New node Link as NULL.
	new->sub_link = create_sub_node (f_name);				//Create the File details List and link it to the New node.
	new->f_count = 1;		//Update the File Count as 1 initially.

	if (*head == NULL)		//If the File List is empty, make the New node as the Head of the Word List.
	{
		*head = new;
		return SUCCESS;
	}

	main_node_t* temp = *head;
	while (temp->link != NULL)	//Traverse to insert the New node at the end of List.
	{
		temp = temp->link;	//Update the 'temp' to point to the Next node.
	}

	temp->link = new;		//Update the Last node pointer to point to the New node.

	return SUCCESS;
}

/* To Create a Node with given File details
 * Input: File Name
 * Output: Node with File details
 * Return Value: Sub-List Node
 */
sub_node_t* create_sub_node (char* f_name)
{
	sub_node_t* new = (sub_node_t*) malloc (sizeof (sub_node_t));	//Dynamic Memory allocation for adding the File details in the Sub-List of the Word List.
	strncpy (new->f_name, f_name, (strlen (f_name) + 1));		//Copy the File name into the New node Data.
	new->w_count = 1;	//Update the Word Count as 1 initially.
	new->link = NULL;	//Update the New node Link as NULL.
	return new;
}
