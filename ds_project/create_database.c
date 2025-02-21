#include "main.h"

/* To Create the Database for the given File List
 * Input: File List and Hash Table
 * Output: Filled Hash Table
 * Return Value: SUCCESS
 */

int create_DB (file_node_t* file_head, main_node_t** head)
{
	while (file_head != NULL)		//The loop shall run till all the Files in the File List are read.
	{
		read_datafile (head, file_head->f_name);	//The function call to read all the Words in the particular File.

		printf ( "INFO: Database creation for the File %s Successful.\n" , file_head->f_name);
		file_head = file_head->link;	//Update the 'file_head' to point to the Next node.
	}

	return SUCCESS;
}

/* To Insert all the Words in a given File into the Hash Table
 * Input: Hash Table and File Name
 * Output: Filled Hash Table
 * Return Value: NIL
 */

void read_datafile (main_node_t** head, char* f_name)
{
	FILE* fptr = fopen (f_name, "r");
	if (fptr == NULL)	//Error Handling.
		return;

	fseek (fptr, 0L, SEEK_SET);	//To start reading the File from the Beginning.

	char buffer [BUFF_SIZE];	//To store the string read from the File.
	int val;	//To store the return value from the 'fscanf()'.
	int key;	//To store the Key for a particular string.
	int ret;
	
	do
	{
		memset (buffer, '\0', BUFF_SIZE);	//To reset the Buffer with '\0' before reading the next string from the File.
		val = fscanf (fptr, "%s", buffer);
		if (val != 0)	//Error Handling for 'fscanf()'.
		{
			if ((strlen (buffer)) != 0)		//To check if the Word read from the File is Valid or not.
			{
				key = get_key (buffer [0]);	//To calculate the Index in the Hash Table where this string shall be inserted.
				
				ret = check_word (buffer, head [key]);
				if (ret == FAILURE)		//If the Word is not present in the Database, it shall be inserted as a New Word in the Database.
				{
					ret = insert_at_last_main (&head [key], buffer, f_name);
					if (ret == FAILURE)	//If the Word is not added, the process shall terminate.
					{
						printf ( "ERROR: Unable to add the Word \"%s\" in the Database.\n", buffer);
						return;
					}
				}
				else	//If the Word is already present in the Database, then the Sub-List shall be checked if the File details are already present or not.
				{
					ret = check_file (f_name, buffer, head [key]);
					if (ret == FAILURE)	//If the File details of the particular Word is not present in the Sub-List, is shall be inserted as a New File details in the Database.
					{
						ret = update_link_table (&head [key], buffer, f_name);
						if (ret == FAILURE)	//If the File details are not added, the process shall terminate.
						{
							printf ( "ERROR: Unable to add the File \"%s\" details for the Word \"%s\" in the Database.\n", f_name, buffer);
							return;
						}
						
					}
					else	//If the File details are already present in the Sub-List, the Word count shall be updated in the Database.
					{
						ret = update_word_count (&head [key], buffer, f_name);
						if (ret == FAILURE)
						{
							printf ("ERROR: Unable to Update the Word Count for the Word \"%s\" in the File \"%s\"\n", buffer, f_name);
							return;
						}
					}
				}
			}
		}
	} while (val != EOF);	//The loop shall run till we reach the End of the File.

	fclose (fptr);		//Close the opened File.
	return;
}

/* To Insert the File Details in the Sub-List of the particular Word details in the Hash Table
 * Input: Hash Table, Given Word and Given File Name
 * Output: File Details added in the Sub-List
 * Return Value: SUCCESS or FAILURE
 */

int update_link_table (main_node_t** head, char* word, char* f_name)
{
	main_node_t* temp1 = *head;
	while (temp1 != NULL)		//The loop shall run till all the Words in the List of the Key are compared with 'word'.
	{
		if (strncmp (temp1->word, word, BUFF_SIZE) == 0)	//If the 'word' matches with the exisiting Words stored in the List of the Key, insert the File details.
		{
			sub_node_t* temp2 = temp1->sub_link;
			while (temp2->link != NULL)	//The loop shall run till the end of the Sub-List of the particular Word.
			{
				temp2 = temp2->link;	//Update the 'temp2' to point to the Next node.
			}
			
			temp2->link = create_sub_node (f_name);		//Insert the File details as the Last Node of the Sub-List of the particular Word.
			if (temp2->link == NULL)	//Error Handling.
				return FAILURE;
			else
				temp1->f_count += 1;	//If the File details are added successfully, increment the File Count in the Node of the particular Word by 1.
		}

		temp1 = temp1->link;	//Update the 'temp1' to point to the Next node.
	}
	
	return SUCCESS;
}

/* To Update the Word Count in the File details in the Sub-List
 * Input: Hash Table, Given Word and Given File Name
 * Output: Word Count updated in the File Sub-List
 * Return Value: SUCCESS or FAILURE
 */

int update_word_count (main_node_t **head, char* word, char* f_name)
{
	main_node_t* temp1 = *head;
	while (temp1 != NULL)		//The loop shall run till all the Words in the List of the Key are compared with 'word'.
	{
		if (strncmp (temp1->word, word, BUFF_SIZE) == 0)	//If the 'word' matches with the exisiting Words stored in the List of the Key, insert the File details.
		{
			sub_node_t* temp2 = temp1->sub_link;
			while (temp2 != NULL)			//The loop shall run till the end of the Sub-List of the particular Word.
			{
				if (strncmp (temp2->f_name, f_name, NAMELENGTH) == 0)	//If the 'f_name' matches with the existing files stored in the List, update the Word Count for the File.
				{
					temp2->w_count += 1;	//If the Word & the File details are matched successfully, increment the Word Count in the particular File by 1.
					return SUCCESS;
				}

				temp2 = temp2->link;    	//Update the 'temp2' to point to the Next node.
			}
		}

		temp1 = temp1->link;	//Update the 'temp1' to point to the Next node.
	}
	
	return FAILURE;
}
