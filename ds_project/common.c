#include "main.h"

/* Check which Files are Valid and Store them in File List
 * Input: Empty File List and Command Line Arguments
 * Output: The File List containing the Valid File Names
 * Return Value: NIL 
 */

void validate_n_store_filenames (file_node_t** files_h, char* filenames[])
{
	int i = 1, ret;	

	while (filenames [i] != NULL)		//The loop shall run to Validate each File name passed in the Command Line.
	{
		ret = IsFileValid (filenames [i]);
		if (ret == SUCCESS)		//If the File name is valid, proceed to check if it is repeated or not.
		{
			ret = IsFileDuplicate (filenames [i], files_h);
			if (ret == FAILURE)	//If the File name is not present in the File List; proceed to add it into the File List.
			{
				ret = store_filenames_to_list (filenames [i], files_h);
				if (ret == SUCCESS)	//If the File name is added to the File List successfully, print a confirmation message.
				{
					printf ("INFO: The File %s is added to the List Successfully.\n" , filenames [i]);
				}
			}
		}
		i += 1;	//Move to the next File name passed in the Command Line.
	}

	if (*files_h == NULL)	//If no File is added to the File Name List; print an error message and terminate the Operation.
	{
		printf ( "ERROR: There is no Valid File passed as Input.\n INFO: Please enter names of Valid Files only.\n");

		exit (0);	//To Terminate the entire Operation as there are no Valid Files to be operated on.
	}

	return;
}

/* Check if the File is Valid and it's Content Size
 * Input: File Name
 * Output: Valid Non-Empty File Name
 * Return Value: SUCCESS or FAILURE
 */

int IsFileValid (char* filename)
{
	FILE* fptr = fopen (filename, "r");
	if (fptr == NULL)	//If there is an error in Opening the File or if the File doesn't exists, the particular File cannot be added to the Database.
	{
		printf ("ERROR: The File %s is not present.\n INFO: So, this File cannot be added into the Database.\n", filename);
		return NOT_PRESENT;
	}
	else			//The File is Opened successfully.
	{
		fseek (fptr, 0L, SEEK_END);
		int pos = ftell (fptr);

		if (pos == 0)	//If the File is Empty i.e. the end position of the File is '0'; the particular File cannot be added to the Database.
		{
			printf("ERROR: The File %s is an Empty File.\n INFO: So, this File cannot be added into the Database.\n", filename);
			return FILE_EMPTY;
		}
		else
		{
			fclose (fptr);	//Close the opened File.
			return SUCCESS;
		}
	}
}

/* Check if the File is already present in the File List
 * Input: File Name and File List
 * Output: Non-Duplicate File Name
 * Return Value: SUCCESS or FAILURE
 */

int IsFileDuplicate (char* filename, file_node_t** head)
{
	file_node_t* temp = *head;

	while (temp != NULL)	//The loop shall run till the end of the File List and compare each File name with the given 'filename'.
	{
		if ((strncmp (filename, temp->f_name, NAMELENGTH)) == 0)	//If the File Name in File List matches with the given 'filename'; it is not required to insert it again.
		{
			printf ("ERROR: The File %s is repeated.\n INFO: So, this File cannot be added into the Database.\n", filename);
			return REPEATED;
		}
		
		temp = temp->link;
	}

	return FAILURE;
}

/* Store the Non-Empty, Valid and Non-Duplicate File Names in the File List
 * Input: File Name and File List
 * Output: File List with the given File Name
 * Return Value: SUCCESS or FAILURE
 */

int store_filenames_to_list (char* f_name, file_node_t** head)
{
	int ret = insert_at_last_file (head, f_name);
	if (ret == FAILURE)		//If the File Name is not added, the process shall terminate.
	{
		printf ("ERROR: Unable to add the File %s into the File List.\n", f_name);
		return FAILURE;
	}
	
	return SUCCESS;
}

/* Calculate the Key for the given Word to place in the Hash Table
 * Input: Given Word's First Character
 * Output: Key for the given Word
 * Return Value: Integer
 */

int get_key (char f_char)
{
	/* Hash Function for the Hash Table = Data % {65 (Upper-case) or 97 (Lower-case)}
	   If the string is a Special character or Digits; store in the separate Key.
	 */

	if (isalpha (f_char))		//If the First character is an Alphabet; the Key will have a value between 0 to 25.
	{
		f_char = (char) toupper (f_char);
		return (f_char % 65);
	}
	else if (isdigit (f_char))	//If the First character is a Digit; the Key will have a value of 26.
	{
		return 26;
	}
	else				//If the First character is a Special Character; the Key will have a value of 27.
	{
		return 27;
	}
}

/* Check if the Word is already present in the Hash Table
 * Input: Given Word and Hash Table
 * Output: Word Status in the Hash Table
 * Return Value: REPEATED or FAILURE
 */

int check_word (char* word, main_node_t* head)
{
	while (head != NULL)		//The loop shall run till all the Words in the List of the Key are compared with 'word'.
	{
		if (strncmp (head->word, word, BUFF_SIZE) == 0)		//If the 'word' matches with the exisiting Words stored in the List of the Key, it is not required to insert it again.
			return REPEATED;

		head = head->link;	//Update the 'head' to point to the Next node.
	}

	return FAILURE;
}

/* Check if the Given Word's File details are already present in the Hash Table
 * Input: Given File Name, Given Word and Head pointer for the Word details List
 * Output: File Status in the Word List
 * Return Value: REPEATED or FAILURE
 */

int check_file (char* f_name, char* word, main_node_t* head)
{
	while (head != NULL)	//The loop shall run till all the Words in the List of the Key are compared with 'word'.
	{
		if (strncmp (head->word, word, BUFF_SIZE) == 0)	//If the 'word' matches with the exisiting Words stored in the List of the Key, check for the File details in the Sub-List.
		{
			sub_node_t* temp = head->sub_link;
			while (temp != NULL)	//The loop shall run till all the Files in the List for the particular Word are compared with 'f_name'.
			{
				if (strncmp (temp->f_name, f_name, NAMELENGTH) == 0)	//If the 'f_name' matches with the existing files stored in the List, it is not required to insert it again.
					return REPEATED;
				
				temp = temp->link;	//Update the 'temp' to point to the Next node.
			}
		}

		head = head->link;		//Update the 'head' to point to the Next node.
	}

	return FAILURE;
}
