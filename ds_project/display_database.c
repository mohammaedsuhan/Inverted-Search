#include "inverted_index.h"

/* To Display the Complete details in the Database
 * Input: Hash Table
 * Output: Complete Word & File Details in the Hash Table
 * Return Value: SUCCESS or FAILURE
 */

int display_DB (main_node_t** head)
{
	int i = 0, flag = 0;

	while (i < SIZE)		//The loop shall run to go through the Complete Database and print each Word in each File.
	{
		if (head [i] != NULL)	//If the particular Key has no words, then that Key shall be ignored.
		{
			display_words (head [i], i);
			flag = 1;
		}

		i += 1; 		//Update the Key value to go to the next Word in the List.
	}

	if (flag == 0)			//If the Database is empty, none of the Keys will be printed (as their Heads will be NULL).
		return FAILURE;
	else
		return SUCCESS;
}

/* To Display the Complete details of a particular Word in the Hash Table
 * Input: Head pointer of the Word and Key
 * Output: Complete details of a particular Word
 * Return Value: NIL
 */

void display_words (main_node_t* temp1, int index)
{
	while (temp1 != NULL)		//The loop shall run till we reach the end of the Word List.
	{
		printf ("[%d]\t", index);
		printf ( "[%-10s]\t", temp1->word);
		printf ( "%d"  " File(s) :\t", temp1->f_count);
				
		display_files (temp1->sub_link);
		
		printf ("-> NULL\n");	//Signifies the end of the Sub-List.
		temp1 = temp1->link;	//Update the 'temp1' to point to the Next node.
	}
}

/* To Display the Complete details of the File Sub-List of the given Word
 * Input: Head pointer of the File Sub-List
 * Output: Complete File details of a particular Word
 * Return Value: NIL
 */

void display_files (sub_node_t* temp2)
{
	while (temp2 != NULL)		//The loop shall run till we reach the end of the Sub-List.
	{
		printf ("File : %s\t" , temp2->f_name);
		printf ( "%d"  " time(s)\t", temp2->w_count);
		
		temp2 = temp2->link;	//Update the 'temp2' to point to the Next node.
		
		if (temp2 != NULL)	//If we have not reached the end of the List, then print the Separator.
			printf (":\t");
	}
}
