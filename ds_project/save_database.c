#include "inverted_index.h"

/* To Save the Current Database into a given File
 * Input: Hash Table and File Name
 * Output: File having Hash Table details in a particular Format
 * Return: SUCCESS or FAILURE
 */

int save_DB (main_node_t **head, char *fname)
{
	char name [NAMELENGTH];
	strncpy (name, fname, NAMELENGTH);

	int ret = check_name (fname);
	if (ret == FAILURE)		//If the User has not provided any Extension along with the File Name; append the default extension of '.txt'.
	{
		strncat (name, ".txt", 4);
	}
		
	FILE* fptr = fopen (name, "w");
	if (fptr == NULL)		//Error Handling.
	{
		printf ( "ERROR: Unable to open the File %s.\n" , name);
		return FAILURE;
	}

	int i = 0;

	while (i < SIZE)		//The loop shall run to go through the Complete Database and store each Word of each File in the File.
	{
		if (head [i] != NULL)	//If the particular Key has no words, then that Key shall be ignored.
		{
			main_node_t* temp1 = head [i];
			fprintf (fptr, "#%d;\n", i);

			while (temp1 != NULL)			//The loop shall run till we reach the end of the Word List.
			{
				fprintf (fptr, "%s;", temp1->word);
				fprintf (fptr, "%d;", temp1->f_count);
				
				sub_node_t* temp2 = temp1->sub_link;
				
				while (temp2 != NULL)		//The loop shall run till we reach the end of the Sub-List.
				{
					fprintf (fptr, "%s;", temp2->f_name);
					fprintf (fptr, "%d;", temp2->w_count);
					temp2 = temp2->link;	//Update the 'temp2' to point to the Next node.
				}

				fprintf (fptr, "#\n");
				temp1 = temp1->link;		//Update the 'temp1' to point to the Next node.
			}
		}

		i += 1;		//Update the Key value to go to the next Word in the List.
	}

	fclose (fptr);		//Close the File Opened.
	return SUCCESS;
}

/* To Check if the given File Name has any Extension or not
 * Input: File Name
 * Output: File Name with Extension
 * Return Value: SUCCESS or FAILURE
 */
int check_name (char* fname)
{
	char* str = strstr (fname, ".");	//If the Extension is absent from the File Name, the value stored in 'str' will be NULL.

	if (str == NULL)
		return FAILURE;
	else
		return SUCCESS;
}
