#include "inverted_index.h"

/* To Update the Database with the Words in a given File
 * Input: File List, Hash Table and given File Name
 * Output: Updated File List and Hash Table
 * Return Value: SUCCESS or FAILURE
 */

int update_DB (file_node_t** files_h, main_node_t** head, char* f_name)
{
	int ret;

	if ((IsFileValid (f_name)) == SUCCESS)		//If the File name is valid, proceed to check if it is repeated or not.
	{
		if ((IsFileDuplicate (f_name, files_h)) == FAILURE)	//If the File name is not present in the File List; proceed to add it into the File List.
		{
			ret = store_filenames_to_list (f_name, files_h);
			if (ret == SUCCESS)		//If the File name is added to the File List successfully, print a confirmation message.
			{
				printf ( "INFO: The File %s is added to the List successfully.\n" , f_name);
				
				read_datafile (head, f_name);		//The function call to read all the Words in the given 'f_name' File.

				printf ("INFO: Database creation for the File %s Successful.\n" , f_name);

				return SUCCESS;
			}
		}
	}

	/* If any of the above conditions fail, the File cannot be Updated in the Database. */
	return FAILURE;
}
