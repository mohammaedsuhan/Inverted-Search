#include<stdio.h>
#include<string.h>
#include"main.h"
int file_validate(int argc, char *argv[])
{
    FILE *fptr;
    if(argc > 1)      
    {
	for(int i=1;i<argc;i++)
	{
	    if(strstr(argv[i],".txt")==0)   
	    {
		printf("[ %s ] is not a [.txt] file\n",argv[i]);
		argv[i] = NULL;
	    }

	    if(argv[i] != NULL)
	    {
	        fptr=fopen(argv[i],"r"); 
	        if(fptr == NULL)          
	        {
		    printf("FILE NOT EXIST ");
		    argv[i] = NULL ;
	        }
	        else if(fptr != NULL)
	        {
	            fseek(fptr,0,SEEK_END);
	            if(ftell(fptr)==0)    
	            {
	 	        printf("Empty file");
		        argv[i]= NULL;
	            } 
	        }
	    }
	    
	}
	return SUCCESS;
    }
    else
	return FAILURE;
}
