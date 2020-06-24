//  main.c
//  Operating System lab 1
//
//  Created by Kartikey Sharan on 13/02/20.
//  Copyright © 2020 Kartikey Sharan. All rights reserved.
//

#define _GNU_SOURCE

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <stdbool.h>

#define WHITESPACE " \t\n" //To split command line into token we should define delimeter,
                           //the whitespace will be our delimeter
#define MAX_COMMAND_SIZE 255 //Max size of command line
#define MAX_NUM_ARGUMENTS 10 //MAV Shell will only support 10 command line parameters
#define _GNU_SOURCE
#define MAX_HISTORY 15 // The max number of most-recent commands to be kept
#define MAX_PIDS 15 // The max number of most-recent precesses spawned to be kept
bool exceeded_history_count = false; //Boolean to check the number of history count
bool exceeded_pid_count = false; // Boolean to check number of pid count

int main()
{
    char * cmd_str = (char*) malloc(MAX_COMMAND_SIZE); // command history list
    char* hist[MAX_HISTORY]; // MAX_HISTORY sets ceiling for number of Commands
    pid_t pid=0;
    int d;
    int counter = 0; // keeps track of number of commands that have been called throughout the user session
    for (d = 0; d < MAX_HISTORY; d++) //Copying the user commands into the history array by using malloc and memset to allocate memory to avoid seg fault
    {
        hist[d] = (char*)malloc(255);
    }
    pid_t showpids[MAX_PIDS];  //list of pids
    while(1)
    {
        printf ("msh> ");     // Print out the msh prompt
        // Read the command from the commandline.  The
        // maximum command that will be read is MAX_COMMAND_SIZE
        // This while command will wait here until the user
        // inputs something since fgets returns NULL when there
        // is no input
        while(!fgets(cmd_str, MAX_COMMAND_SIZE, stdin));
        if (counter > 15)
        {
            int i;
            for(i = 0; i< MAX_HISTORY; i++)
            {
                strcpy(hist[i],hist[i+1]);
            }
        }
        else
        {
          strncpy(hist[counter],cmd_str,strlen(cmd_str)+1);
        }
        if(counter == 15)
        {
          counter = 0;
          exceeded_history_count = true;
        }
        if (cmd_str[0] == '!')
        {
            strncpy(cmd_str, hist[atoi(&cmd_str[1])], strlen(hist[atoi(&cmd_str[1])])+1);
        }
        char *token[MAX_NUM_ARGUMENTS]; // Parse input
        int token_count=0;
        char *arg_ptr; // Pointer to point to the token
                        // parsed by strsep
        char *working_str= strdup(cmd_str);
        // we are going to move the working_str pointer so
        // keep track of its original value so we can deallocate
        // the correct amount at the end
        char *working_root= working_str;
        // Tokenize the input stringswith whitespace used as the delimiter
        while ( ( (arg_ptr = strsep(&working_str, WHITESPACE ) ) != NULL) &&
                  (token_count<MAX_NUM_ARGUMENTS))
        {
          token[token_count] = strndup( arg_ptr, MAX_COMMAND_SIZE );
          if( strlen( token[token_count] ) == 0 )
          {
            token[token_count] = NULL;
          }
            token_count++;
        }
        // Now print the tokenized input as a debug check
        // \TODO Remove this code and replace with your shell functionality
        //Shell functionality
        //to avoid seg fault when user gives no input
        if( token[0] == NULL )
        {
            continue; //do nothing
        }
        //Exit the session when user enters quit or exit
        else if(strcmp(token[0], "quit")==0)
        {
            exit(0);
        }
        else if(strcmp(token[0],"exit")==0)
        {
            exit(0);
        }
        //User can change the current directory by using the command cd followed by name of directory to access
        else if(strcmp(token[0],"cd")==0)
        {
                chdir(token[1]);
             
        }
        //entering the command history will dislpay the last few commands from MAX_HISTORY
        else if(strcmp(token[0],"history")==0)
        {
            int j;
            //boolean set to count so that number of user commands displayed don't exceed maximum history
            if (exceeded_history_count)
            {
                //Print history
                for(j=0; j < MAX_HISTORY; j++)
                {
                    printf("%d: %s\n", j, hist[j]);
                }
            }
            else
            {
              for(j=0; j < counter; j++)
                {
                    printf("%d: %s\n", j, hist[j]);
                }
            }
        }
        else if(strcmp(token[0], "showpids")==0)
        {
            int j;
            //boolean set to count so that number of PIDs displayed don't exceed maximum showpids
            if (exceeded_pid_count)
            {
               //Print PIDs
                for(j=0; j<MAX_PIDS; j++)
                {
                printf("%d: %d\n", j, showpids[j]);
                }
            }
            else
            {
                for(j=0; j<counter; j++)
                {
                    printf("%d: %d\n", j, showpids[j]);
                }
                
            }
        }
        else
        {
            
            pid = fork();
            //Add the current pid to the showpid display list
            showpids[counter] = pid;
            if(counter == 15)
            {
              counter = 0;
              exceeded_pid_count = true;
            }
            if(pid == -1)
            {
                perror("fork failed");
                exit(EXIT_FAILURE);
            }
            //child pid
            else if(pid == 0)
            {
               
                execvp(token[0],token);
                printf("Command not found \n");
                fflush(NULL);
                exit(EXIT_SUCCESS);
            }
            else
            {
                int stat;
                //waiting for stat
                wait(&stat);
                fflush(NULL);
            }
        }
            //Increment the counter
            counter++;
            free(working_root);
    }
    return 0;
        
}
