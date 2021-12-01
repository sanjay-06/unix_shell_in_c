#include <stdio.h>
#include <windows.h>
#include <unistd.h>
#include <iostream>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string>
#include <Windows.h>

class Pipe
{
	BOOL bCreatePipe;
	HANDLE hRead;
	HANDLE hWrite;
	char  szBuffer[256];
	DWORD dwBufferSize;
	BOOL bWritefile;
	BOOL bReadfile;
	DWORD dwNoBytesWrite;
	DWORD dwNoBytesRead;
public:
	
void set_sz(char s[256])
{
	strcpy(szBuffer,s);
	dwBufferSize=sizeof(szBuffer);
}
void createpipe()
{
		
	bCreatePipe=CreatePipe(
	&hRead,
	&hWrite,
	NULL,
	dwBufferSize
	);
	
}
void writepipe()
{
	bWritefile=WriteFile(
	hWrite,
	szBuffer,
	dwBufferSize,
	&dwNoBytesWrite,
	NULL
	);
	CloseHandle(hWrite);
}
char* readpipe()
{
	bReadfile=ReadFile(
	hRead,
	szBuffer,
	dwBufferSize,
	&dwNoBytesWrite,
	NULL
	);
	CloseHandle(hRead);
	return szBuffer;
}
};

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
		    	printf("Implementation of unix shell [Version 1.0] \n (c) Done by sanjay and saravnan.All rights reserved.\n\nTo view list of commands --> compgen\nGet help about a command --> man <COMMAND NAME>\n\n");
}

char Commands[][10] = {"man","echo","wc","clear","cat","rm","cd","pwd","mkdir","rmdir","ls","cp","exit","touch","compgen"};

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

char *echo(char *s)
{
	return s;
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
void ls(char ret[256][256])
{
	char *s=pwd();
    struct dirent *entry = NULL;
    DIR *dp = NULL;
    dp = opendir(s);
    int i=0;
    if (dp != NULL)
    {
        while ((entry = readdir(dp)))
        {
            strcpy(ret[i],entry->d_name);
            i++;
        }
    }
    closedir(dp);
    strcpy(ret[i],"NULL");
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


void cat(char *s,char *option="\0",int *index=0)
{
	if (option=="\0")
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
		    int i=*index;
		  
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
		    		printf("\n%d ",++i);
				}
		        printf ("%c", c);
		        if(c=='\n')
		    	{
		    		printf("%d ",++i);
		    		
				}
		        c = fgetc(fptr);
		    }
		    fclose(fptr);
		    *index=i;
		}
	}
}

void wc(char *s,char *set="\0")
{
	if (set=="\0")
	{
		FILE* fp = fopen(s, "r");
	    if (fp == NULL) {
	        printf("File Not Found!\n");
	    }
	  
	    fseek(fp, 0L, SEEK_END);
	  
	    long int res = ftell(fp);
	    fseek(fp, 0L, SEEK_SET);
	    char ch=fgetc(fp);
        int wrd=0,line=0;
		while(ch!=EOF) 
        {  
                if(ch==' '||ch=='\n')
                    { 
                        if(ch=='\n')
                        {
                        	line++;
						}
                        wrd++; 
                    }
                ch=fgetc(fp); 
        }
        fclose(fp);
		printf("%d %d %ld \n",line,wrd,res);
		
	}
	else if(set=="|")
	{
		int word=0;
		int line=0;
		int i;
		int byte=strlen(s);
		strcat(s,"\n");
		for(i=0;i<byte+1;i++)
		{
			if(s[i]=='\n')
			{
				word++;
				line++;
			}
			if(s[i]==' ')
			{
				word++;
			}
		}
		printf("%d %d %d \n",line,word,byte);
	}
	
	
}
void compgen()
{
	int i;
	printf("\n");
	for(i=0;i<15;i++)
	{
		printf("%s\n",Commands[i]);
	}
	printf("\nPipe supporting commands --> \n pwd | wc \n pwd | echo \n pwd | cat \n ls | wc \n ls | echo \n ls | cat ");
	printf("\nOutput Redirection commands --> \n ls > <filename> \n pwd > <filename>\n echo <string> > <filename>\n");
	
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

void split(char *command, char *commandsplit[],int length)
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
    *commandsplit = "\0";
}

void man(char *s)
{
	if(!isValidCommand(s))
	{
		printf("Command not found\n");
	}
	else
	{
		strcat(s,".txt");
		char fname[256];
		strcpy(fname,"man\\");
		strcat(fname,s);
		FILE *fp=fopen(fname,"r");
		if (fp == NULL)
	    {
	        perror("Error ");
	    }
	
	    char c = fgetc(fp);
	    while (c != EOF)
	    {
	        printf ("%c", c);
	        c = fgetc(fp);
	    }
	  
	    fclose(fp);
	}
	
}
void write(char *filename,char *s)
{
	FILE *fp=fopen(filename,"w");
	int result =fputs(s,fp);
	fclose(fp);
}

int present(char* op,char * splits[])
{
    while (*splits != "\0")
    {
        if (strcmp(op,*splits)==0)
        {
            return 1;
        }
        *splits++;
    }
    return 0;
}

int main()
{
	Pipe p;
    HWND consoleWindow = GetConsoleWindow();
    ShowWindow(consoleWindow, SW_MAXIMIZE);
    welcome();
    char Command[256];
    char backup[strlen(Command)];
    strcpy(backup,Command);
    char *commandsplit[10];
    while(1)
    {
        printf("\n%s",pwd());
        printf("> ");
        fgets(Command,1024,stdin);
        split(Command,commandsplit,strlen(Command)-1);
        if (!(isValidCommand(commandsplit[0])))
        {
            printf("Command not found\n");
            continue;
        }
        int mid,last,i;
        char s[3];
        
        
        if(present("|",commandsplit))
        {
        
        	i=0;
		    while (commandsplit[i] != "\0")
		    {
		        if (strcmp("|",commandsplit[i])==0)
		        {
		        	mid=i;
		        }
		        commandsplit[i];
		        i++;
		    }
            last = i;
            int len = sizeof(commandsplit)/sizeof(commandsplit[0]);
            char left[3][100];
            char right[3][100];
            for(i=0;i<mid;i++)
            {
                strcpy(left[i],commandsplit[i]);
            }

            len = sizeof(left)/sizeof(left[0]);
            int j=0;
            for(i=mid+1;i<last;i++)
            {
                strcpy(right[j],commandsplit[i]);
                j++;
            }

            if(strcmp(left[0],"pwd")==0)
            {

                char *s=pwd();
                p.set_sz(s);
                p.createpipe();
                p.writepipe();
            }
            else if(strcmp(left[0],"ls")==0)
            {
                char ret[256][256];
                ls(ret);
                int i=0,size=0;
                while(strcmp(ret[i],"NULL"))
                {
                
                	ret[i++];
                    size++;
                }
                char s[256]="";
                int k=0;
                for (int i=0; i < size; i++)
                {
			        for (int j=0; j < strlen(ret[i]); j++)
			        {
			            s[k]+=ret[i][j];
			        	k++;
					}
					if(i!=size-1)
					{
						s[k]+='\n';	
					}
					k++;
			    }
                p.set_sz(s);
              
                p.createpipe();
                
                p.writepipe();
                
            }
            
            if(strcmp(right[0],"cat")==0)
            {        	
			   	printf("%s",p.readpipe()); 
                
            }
            else if(strcmp(right[0],"echo")==0)
            {
            	printf("%s",echo(p.readpipe())); 
            }
            else if(strcmp(right[0],"wc")==0)
            {
            	wc(p.readpipe(),"|"); 
            }
        }
        
        
        else if(present(">",commandsplit))
        {
        
        	i=0;
        	int mid=0;
        	int last;
		    while (commandsplit[i] != "\0")
		    {
		        if (strcmp(">",commandsplit[i])==0)
		        {
		        	mid=i;
		        }
		        commandsplit[i];
		        i++;
		    }
            last = i;
            int len = sizeof(commandsplit)/sizeof(commandsplit[0]);
            char left[3][100];
            char right[3][100];
            for(i=0;i<mid;i++)
            {
                strcpy(left[i],commandsplit[i]);
            }

            len = sizeof(left)/sizeof(left[0]);
            int j=0;
            for(i=mid+1;i<last;i++)
            {
                strcpy(right[j],commandsplit[i]);
                j++;
            }

            if(strcmp(left[0],"pwd")==0)
            {

                char *s=pwd();
                char a[strlen(s)+1];
                strcpy(a,s);
                write(right[0],a);
            }
            else if(strcmp(left[0],"ls")==0)
            {
                char ret[256][256];
                ls(ret);
                int i=0,size=0;
                while(strcmp(ret[i],"NULL"))
                {
                
                	ret[i++];
                    size++;
                }
                char s[256]="";
                int k=0;
                for (int i=0; i < size; i++)
                {
			        for (int j=0; j < strlen(ret[i]); j++)
			        {
			            s[k]+=ret[i][j];
			        	k++;
					}
					s[k]+='\n';
					k++;
			    }
                write(right[0],s);
                
            }
            
            else if(strcmp(left[0],"echo")==0)
            {
                write(right[0],echo(left[1]));
                
            }
		}  
        
		else if (strcmp(commandsplit[0],"cd")==0)
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
            int i = 1;
            while (commandsplit[i] != "\0")
            {
                mkdirt(commandsplit[i]);
                i++;
            }
        }
        else if(strcmp(commandsplit[0],"rmdir")==0)
        {
            int i = 1;
            while (commandsplit[i] != "\0")
            {
                rmdirt(commandsplit[i]);
                i++;
            }
        }
        else if(strcmp(commandsplit[0],"ls")==0)
        {
        	char ret[256][256];
            ls(ret);
			int i=0;
            while(strcmp(ret[i],"NULL"))
            {
            	printf("%s\n",ret[i++]);
			}
        }
        else if(strcmp(commandsplit[0],"cp")==0)
        {
            cp(commandsplit[1],commandsplit[2]);
        }
        else if(strcmp(commandsplit[0],"touch")==0)
        {
            int i = 1;
            while (commandsplit[i] != "\0")
            {
                touch(commandsplit[i]);
                i++;
            }
        }
        else if(strcmp(commandsplit[0],"rm")==0)
        {
            int i = 1;
            while (commandsplit[i] != "\0")
            {
                rm(commandsplit[i]);
                i++;
            }
        }
         else if(strcmp(commandsplit[0],"cat")==0)
        {
            
            int index=0;
            
        	if(strcmp(commandsplit[1],"-n")==0)
        	{
        		int i = 2;
        		while (commandsplit[i] != "\0")
        		{
        			cat(commandsplit[i],commandsplit[1],&index);
        		    i++;
        		}
			}
			else
			{
				int i=1;
			    while (commandsplit[i] != "\0")
        		{
        			cat(commandsplit[i],"\0",&index);
        		    i++;
        		}
			}
        }
		else if(strcmp(commandsplit[0],"wc")==0)
        {
            wc(commandsplit[1],commandsplit[2]);
        }
		else if(strcmp(commandsplit[0],"clear")==0)
        {
            system("cls");
        }
        else if(strcmp(commandsplit[0],"echo")==0)
        {
            printf("%s\n",Command);
        }
        else if(strcmp(commandsplit[0],"compgen")==0)
        {
            compgen();
        }
        else if(strcmp(commandsplit[0],"man")==0)
        {
            man(commandsplit[1]);
        }
        else if(strcmp(commandsplit[0],"exit")==0)
        {
            exit(0);
        }
    }
}

