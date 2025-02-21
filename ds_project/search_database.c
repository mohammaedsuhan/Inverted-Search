#include "inverted_index.h"

/* To Search a particular Word in the Database
 * Input: Hash Table and given Word
 * Output: All the details of the given Word in the Hash Table
 * Return Value: SUCCESS or FAILURE
 */

int search_DB (main_node_t** head, char* word)
{
	int index = get_key (word [0]);			//To get the Key for the given 'word'.

	int ret = check_word (word, head [index]);	//To check if the given 'word' is present at the calculated Key in the Database.
	if (ret == REPEATED)				//If the Word is present in the Database, the 'ret' will have the value of REPEATED.
	{
		main_node_t* temp = head [index];
		while (temp != NULL)
		{
			if (strncmp (temp->word, word, BUFF_SIZE) == 0)
			{
				printf ("INFO: Word \"%s\" is found in the Database and is present in %d File(s).\n" , word, temp->f_count);
				display_files (temp->sub_link);
				printf ("\n");
				return SUCCESS;
			}

			temp = temp->link;
		}
	}
	else	//If the Word is not present in the Database, the 'ret' will have the value of FAILURE.
	{
		printf ("ERROR: Word"  \"%s\" is not present in the Database.\n" , word);
		return FAILURE;
	}
}
