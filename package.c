#include<stdio.h>
#include<windows.h>
#include<unistd.h>
#include<string.h>
#include<dirent.h>
#include <sys/stat.h>

void welcome();
void cd();
char* pwd();
void mkdirt();
void rmdirt();
void ls();
void cp();
int isValidCommand(char*);

void welcome()
{
        	char topic_text[] = "\
            \t\t\t\t          000000  00  00  000000   000000  00  00  000000  00      00     \n\r\
            \t\t\t\t            00    00  00  00       00      00  00  00      00      00     \n\r\
            \t\t\t\t            00    000000  000000   000000  000000  000000  00      00     \n\r\
            \t\t\t\t            00    00  00  00           00  00  00  00      00      00     \n\r\
            \t\t\t\t            00    00  00  000000   000000  00  00  000000  000000  000000 \n\r\
            \n\n\n\n\n\n\r\t\t                                                      BY SANJAY AND SARAVANAN \n";
	        printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n%s", topic_text);
		    sleep(2);
		    system("cls");
		    printf("Implementation of unix shell [Version 1.0] \n (c) Done by sanjay and saravnan.All rights reserved.\n\n\n");
}

char Commands[][10] = {"clear","cat","rm","cd","pwd","mkdir","rmdir","ls","cp","exit","touch"};

char* pwd()
{
    char cwd[256];
    if (getcwd(cwd, sizeof(cwd)) == NULL)
    {
    	perror("Error ");
    }
    else
    {
    	char *res=cwd;
        return res;
    }
}

void cd(char s[])
{
	if(!strcmp(s,".."))
	{
		int ch=chdir("..");
	}
	else
	{
	    int ch = chdir(s);
        if(ch<0)
        {
            printf("The system cannot find the path specified.\n");
        }
	}
}

void mkdirt(char *s)
{
    int check = mkdir(s);
    if (!check)
        printf("Directory created\n");
    else
        perror("Error ");
}
void rm(char *s)
{
   int ret = remove(s);

   if(ret == 0) {
      printf("File deleted successfully\n");
   } else {
      printf("Error: unable to delete the file\n");
   }
}

int DirectoryExists(const char *path)
{
    struct stat stats;
    stat(path, &stats);
    if (S_ISDIR(stats.st_mode))
        return 1;

    return 0;
}

void rmdirt(char *s)
{
    int check = rmdir(s);
    if (!check)
        printf("Directory deleted\n");
    else
    {
    	if(DirectoryExists(s))
    	{
    		printf("Not an empty directory\n");
		}
		else
		{
			printf("Unable to delete directory\n");
		}
	}

}

void touch(char *s)
{
	FILE * fPtr;
	fPtr = fopen(s, "w");
	fclose(fPtr);
}

void ls()
{
	char *s=pwd();
    struct dirent *entry = NULL;
    DIR *dp = NULL;
    dp = opendir(s);
    if (dp != NULL)
    {
        while ((entry = readdir(dp)))
        {
            printf ("%s\n", entry->d_name);
        }
    }
    closedir(dp);
}

void cp(char *s1,char *s2)
{
    FILE *fp1, *fp2;
    char ch;
    int pos;

    if ((fp1 = fopen(s1,"r")) == NULL)
    {
        perror("\nError ");
        return;
    }
    else
    {
        printf("File %s opened for copy",s1);
		printf("\nFile %s opened for copy\n",s2);
    }
    fp2 = fopen(s2, "w");
    fseek(fp1, 0L, SEEK_END);
    pos = ftell(fp1);
    fseek(fp1, 0L, SEEK_SET);
    while (pos--)
    {
        ch = fgetc(fp1);
        fputc(ch, fp2);
    }
	fclose(fp1);
	fclose(fp2);
}


void cat(char *s,char *option)
{
	if (option=='\0')
	{
		FILE *fptr;
	  
	    char c;
	  
	    fptr = fopen(s, "r");
	    if (fptr == NULL)
	    {
	        perror("Error ");
	    }
	
	    c = fgetc(fptr);
	    while (c != EOF)
	    {
	        printf ("%c", c);
	        c = fgetc(fptr);
	    }
	  
	    fclose(fptr);
	}
	else
	{
		if(strcmp(option,"-n")==0)
		{
			FILE *fptr;
		  
		    char c;
		    int i=0;
		  
		    fptr = fopen(s, "r");
		    if (fptr == NULL)
		    {
		        perror("Error ");
		    }
		
		    c = fgetc(fptr);
		    while (c != EOF)
		    {
		    	if(i==0)
		    	{
		    		printf("%d ",++i);
				}
		        printf ("%c", c);
		        if(c=='\n')
		    	{
		    		printf("%d ",++i);
				}
		        c = fgetc(fptr);
		    }
		  
		    fclose(fptr);
		}
	}
}
int isValidCommand(char* Command)
{
    int l = sizeof(Commands)/sizeof(Commands[0]);
    int i;
    for (i=0;i<l;i++)
    {
        if (strcmp(Commands[i], Command) == 0)
        {
            return 1;
        }
    }
    return 0;
}

void  split(char *command, char *commandsplit[],int length)
{
    int i;
    command[length]='\0';
    while (*command != '\0')
    {
        while (*command == ' ')
        {
            *command = '\0';
            command++;
        }
        *commandsplit++ = command;
        while (*command != '\0' && *command != ' ')
        {
            command++;
        }
    }
    *commandsplit = '\0';
}

int main()
{
    HWND consoleWindow = GetConsoleWindow(); // This gets the value Windows uses to identify the output window
    ShowWindow(consoleWindow, SW_MAXIMIZE); // this mimics clicking on its' maximize button

    welcome();
    char Command[256];
    char *commandsplit[3];
    while(1)
    {
        printf("\n%s",pwd());
        printf("> ");
        fgets(Command,1024,stdin);
        split(Command,commandsplit,strlen(Command)-1);

        if (!(isValidCommand(commandsplit[0])))
        {
            perror("Command not found\n");
            continue;
        }
        if (strcmp(commandsplit[0],"cd")==0)
        {
            if(commandsplit[1]==NULL)
            {
                printf("Argument to cd command is expected\n");
                continue;
            }
        	cd(commandsplit[1]);
        }
        else if(strcmp(commandsplit[0],"pwd")==0)
        {
            char *s=pwd();
            printf("%s\n",s);
        }
        else if(strcmp(commandsplit[0],"mkdir")==0)
        {
            mkdirt(commandsplit[1]);
        }
        else if(strcmp(commandsplit[0],"rmdir")==0)
        {
            rmdirt(commandsplit[1]);
        }
        else if(strcmp(commandsplit[0],"ls")==0)
        {
            ls();
        }
        else if(strcmp(commandsplit[0],"cp")==0)
        {
            cp(commandsplit[1],commandsplit[2]);
        }
        else if(strcmp(commandsplit[0],"touch")==0)
        {
            touch(commandsplit[1]);
        }
        else if(strcmp(commandsplit[0],"rm")==0)
        {
            rm(commandsplit[1]);
        }
        else if(strcmp(commandsplit[0],"cat")==0)
        {
        	cat(commandsplit[1],commandsplit[2]);
		}
		else if(strcmp(commandsplit[0],"clear")==0)
        {
            system("cls");
        }
        else if(strcmp(commandsplit[0],"exit")==0)
        {
            exit(0);
        }
    }
}
